# Xilinx

## Xilinx SDK

### Baremetal Driver

#### GPIO (gpio)

* void XGpio_SetDataDirection(XGpio *InstancePtr, unsigned Channel, u32 DirectionMask)
  * for dual channels if channel is other than 1

#### AXI IIC (iic)

##### TX data

* `int XIic_MasterSend(XIic *InstancePtr, u8 *TxMsgPtr, int ByteCount)`
  * Put bytes to TX_FIFO, then set MSMS (if not set)
    * only send up to the size of FIFO buffer (based on remaining space from TX_FIFO_OCY)
  * don't write to TX_FIFO if there's only 1 byte
  * Repeated start
    * already MSMS -> repeated start last time -> at the start
      * CntlReg &= ~XIIC_CR_NO_ACK_MASK;
      * CntlReg |= (XIIC_CR_DIR_IS_TX_MASK | XIIC_CR_REPEATED_START_MASK);
    * if not -> start TX by set MSMS at the end:
      * CntlReg &= ~XIIC_CR_NO_ACK_MASK;
      * CntlReg |= XIIC_CR_MSMS_MASK | XIIC_CR_DIR_IS_TX_MASK;
* `static void SendMasterData(XIic *InstancePtr)`
  * ISR
  * handle the last byte
  * reset MSMS if last byte

* `void XIic_TransmitFifoFill(XIic *InstancePtr, int Role)`
  * lower level, called by XIic_MasterSend and SendMasterData
  * if repeated start, send all byte to FIFO
  * if not, send all byte except the last byte

* `#define XIic_WriteSendByte(InstancePtr)`
  * lowest level, one byte only, write to AXI
  * called by everything

##### Interrupt

* XIic_SetSendHandler
  * in example, it is used to set `TransmitComplete = 0`
  * 
* `void XIic_InterruptHandler(void *InstancePtr)` in xiic_intr.c
  * handle interrupt base on different ISR & IER value

#### USB on PS

* [DesignWare USB 3.0 Digital Controller IP](https://www.synopsys.com/dw/ipdir.php?ds=dwc_usb_3_0_controllers) (DWC3) is used
  * [Synopsys DesignWare Core SuperSpeed USB 3.0 Controller - The Linux Kernel](https://www.kernel.org/doc/html/v4.18/driver-api/usb/dwc3.html)

##### struct

```c
/**
 * USB Device Controller representation
 */
struct XUsbPsu {
#if defined (__ICCARM__) // type of compiler used: ICCARM = IAR compiler
    #pragma data_alignment = 64 // compiler option
    SetupPacket SetupData;
    #pragma data_alignment = 64
    struct XUsbPsu_Trb Ep0_Trb;
#else
    // ALIGNMENT_CACHELINE = __attribute__ ((aligned(64)))
    SetupPacket SetupData ALIGNMENT_CACHELINE;
                    /**< Setup Packet buffer */
    struct XUsbPsu_Trb Ep0_Trb ALIGNMENT_CACHELINE;
#endif
                    /**< TRB for control transfers */
    XUsbPsu_Config *ConfigPtr;    /**< Configuration info pointer */

    // eps[0] is EP0 IN, eps[1] is EP0 OUT (I guess, based on XUSBPSU_PhysicalEp())
    struct XUsbPsu_Ep eps[XUSBPSU_ENDPOINTS_NUM]; /**< Endpoints */
    struct XUsbPsu_EvtBuffer Evt;
    struct XUsbPsu_EpParams EpParams;
    u32 BaseAddress;    /**< Core register base address */
    u32 DevDescSize;
    u32 ConfigDescSize;
    struct Usb_DevData *AppData; // .Speed: 2.0 or 3.0
    void (*Chapter9)(struct Usb_DevData *, SetupPacket *);
    void (*ResetIntrHandler)(struct Usb_DevData *);
    void (*DisconnectIntrHandler)(struct Usb_DevData *);
    void *DevDesc;
    void *ConfigDesc;
#if defined(__ICCARM__)
    #pragma data_alignment = XUSBPSU_EVENT_BUFFERS_SIZE
    u8 EventBuffer[XUSBPSU_EVENT_BUFFERS_SIZE];
#else
    u8 EventBuffer[XUSBPSU_EVENT_BUFFERS_SIZE]
                        __attribute__((aligned(XUSBPSU_EVENT_BUFFERS_SIZE)));
#endif
    u8 NumOutEps;
    u8 NumInEps;
    u8 ControlDir;
    u8 IsInTestMode;
    u8 TestMode;
    u8 Ep0State;
    u8 LinkState;
    u8 UnalignedTx;
    u8 IsConfigDone;
    u8 IsThreeStage;
    u8 IsHibernated;                /**< Hibernated state */
    u8 HasHibernation;              /**< Has hibernation support */
    void *data_ptr;        /* pointer for storing applications data */
};
```

* `Usb_DevData`
  * e.g. `UsbInstance`

```c
struct Usb_DevData {
  u8 Speed;
  u8 State;

  void *PrivateData;
};
```

##### Setup

* `main()` in `xusb_pool_example.c`
  * `CfgInitialize()`
    * configure USB on PS
  * `Set_Ch9Handler()`
  * `Set_DrvData()`
    * How Descriptor are pushed
  * `EpConfigure()`
    * 2 EP: 1 OUT, 1 IN
  * `ConfigureDevice()`
    * WTF is this?
    <!-- ? -->
    * ```c
      (void)UsbInstance;
        (void)MemPtr;
        (void)memSize;
        return XST_SUCCESS;
      ```
  * `SetEpHandler()`
    * set up `BulkOutHandler()`, `BulkInHandler()`
  * `UsbEnableEvent()`
    * Events
    <!-- TODO -->
    * > Enable events for Reset, Disconnect, ConnectionDone, Link State Wakeup and Overflow events.
  * `Usb_Start()` = `XUsbPsu_Start()`
    * > Starts the controller so that Host can detect this device.
      <!-- ? -->
      * set `XUSBPSU_DCTL_RUN_STOP` bit in `XUSBPSU_DCTL`
      * `XUsbPsu_Wait_Clear_Timeout()`  
        > Waits until a bit in a register is cleared or timeout occurs
        * blocking
          * used `XUsbSleep(1U)` = `usleep(1U)`
  * `UsbPollHandler()`

* `UsbInstance.PrivateData` = `InstancePtr`
* `InstancePtr->AppData->Speed != XUSBPSU_SPEED_SUPER`
  * define whether USB3.0
  * can be checked with `s32 XUsbPsu_IsSuperSpeed(struct XUsbPsu *InstancePtr)`
* InstancePtrPrivateData
* `u32 Usb_Ch9SetupCfgDescReply(struct Usb_DevData *InstancePtr, u8 *BufPtr, u32 BufLen)`
  * `config3`
    * e.g. descriptor, device class

##### Handle

* Setup Data packet from the host
  * `void Ch9Handler(struct Usb_DevData *InstancePtr, SetupPacket *SetupData)`
    * include `Usb_SetConfigurationApp()`
      * include `EpBufferRecv(InstancePtr->PrivateData, 1, (u8 *)&gst_rx_pkt, MaxPktSize)`
        * queue DMA for Bulk In Transfer
* Bulk Endpoint
  * `void BulkOutHandler(void *CallBackRef, u32 RequestedBytes, u32 BytesTxed)`
    * s32 XUsbPsu_EpBufferSend(struct XUsbPsu *InstancePtr, u8 UsbEp, u8 *BufferPtr, u32 BufferLen)
      * DMA to EP
      * if EP0 is passed, use `XUsbPsu_Ep0Send()`
      * set a lot of register, then `XUsbPsu_SendEpCmd()`
      <!-- TODO -->
    * ParseCBW(InstancePtr)
    * SendCSW(InstancePtr, 0U)
      * For Storage Device (UAS: USB Attached SCSI)
  * `void BulkInHandler(void *CallBackRef, u32 RequestedBytes, u32 BytesTxed)`

* `void UsbPollHandler(struct XUsbPsu *InstancePtr))`
  * = `void XUsbPsu_IntrHandler(void *XUsbPsuInstancePtr)`
  * ```c
    /*
     * Get number of event in register
     * Store in &InstancePtr->Evt
     * Handle in XUsbPsu_EventBufferHandler()
     */
    void XUsbPsu_IntrHandler(void *XUsbPsuInstancePtr) {
        struct XUsbPsu *InstancePtr;
        struct XUsbPsu_EvtBuffer *Evt;
        u32 Count;
        u32 RegVal;

        InstancePtr = (struct XUsbPsu *) XUsbPsuInstancePtr;
        Xil_AssertVoid(InstancePtr != NULL);

        Evt = &InstancePtr->Evt;
        Xil_AssertVoid(Evt != NULL);

        Count = XUsbPsu_ReadReg(InstancePtr, XUSBPSU_GEVNTCOUNT(0U));
        Count &= XUSBPSU_GEVNTCOUNT_MASK;
        /*
        * As per data book software should only process Events if Event count
        * is greater than zero.
        */
        if (Count == 0U) {
            return;
        }

        Evt->Count = Count;
        Evt->Flags |= XUSBPSU_EVENT_PENDING;

        /* Mask event interrupt */
        RegVal = XUsbPsu_ReadReg(InstancePtr, XUSBPSU_GEVNTSIZ(0U));
        RegVal |= XUSBPSU_GEVNTSIZ_INTMASK;
        XUsbPsu_WriteReg(InstancePtr, XUSBPSU_GEVNTSIZ(0U), RegVal);

        /* Processes events in an Event Buffer */
        XUsbPsu_EventBufferHandler(InstancePtr);
    }
    ```

* `void XUsbPsu_EventBufferHandler(struct XUsbPsu *InstancePtr)`
  * While there are still events, put into `Evt` -> `Event` -> `XUsbPsu_EventHandler()`
  
* `void XUsbPsu_EventHandler(struct XUsbPsu *InstancePtr, const union XUsbPsu_Event *Event)`
  *
  <!-- TODO: End point Specific Event? Device Specific Event? -->
  * ```c
    void XUsbPsu_EventHandler(struct XUsbPsu *InstancePtr,
            const union XUsbPsu_Event *Event) {

        if (Event->Type.Is_DevEvt == 0U) {
            /* End point Specific Event */
            XUsbPsu_EpInterrupt(InstancePtr, &Event->Epevt);
            return;
        }

        switch (Event->Type.Type) {
        case XUSBPSU_EVENT_TYPE_DEV:
            /* Device Specific Event */
            XUsbPsu_DevInterrupt(InstancePtr, &Event->Devt);
            break;
            /* Carkit and I2C events not supported now */
        default:
            /* Made for Misra-C Compliance. */
            break;
        }
    }
    ```

* `void XUsbPsu_EpInterrupt(struct XUsbPsu *InstancePtr, const struct XUsbPsu_Event_Epevt *Event)`
  * check if EP0 -> `XUsbPsu_Ep0Intr()`
  * if not EP0, -> `XUsbPsu_EpXferComplete()` / `XUsbPsu_EpXferNotReady()`
  *```c
    void XUsbPsu_EpInterrupt(struct XUsbPsu *InstancePtr,
            const struct XUsbPsu_Event_Epevt *Event) {
        struct XUsbPsu_Ep *Ept;
        u32 Epnum;

        Epnum = Event->Epnumber;
        Ept = &InstancePtr->eps[Epnum];

        if ((Ept->EpStatus & XUSBPSU_EP_ENABLED) == (u32) 0U) {
            return;
        }

        if ((Epnum == (u32) 0U) || (Epnum == (u32) 1U)) {
            XUsbPsu_Ep0Intr(InstancePtr, Event);
            return;
        }

        /* Handle other end point events */
        switch (Event->Endpoint_Event) {
        case XUSBPSU_DEPEVT_XFERCOMPLETE:
        case XUSBPSU_DEPEVT_XFERINPROGRESS:
            XUsbPsu_EpXferComplete(InstancePtr, Event);
            break;

        case XUSBPSU_DEPEVT_XFERNOTREADY:
            XUsbPsu_EpXferNotReady(InstancePtr, Event);
            break;

        default:
            /* Made for Misra-C Compliance. */
            break;
        }
    }
    ```

* `void XUsbPsu_EpXferComplete(struct XUsbPsu *InstancePtr, const struct XUsbPsu_Event_Epevt *Event)`
  * `TrbPtr` look like something related to DMA
    * Pointer to Transfer Request Block, originally in EP's FIFO?
    * ```c
      struct XUsbPsu_Trb {
        u32 BufferPtrLow;
        u32 BufferPtrHigh;
        u32 Size;
        u32 Ctrl;
      } __attribute__((packed));
      ```
    * somewhere: `Xil_DCacheInvalidateRange((INTPTR)TrbPtr, sizeof(struct XUsbPsu_Trb));`
    * FIFO? `TrbPtr = &Ept->EpTrb[Ept->TrbDequeue];`, `Ept->TrbDequeue++;`
  * ```c
    /****************************************************************************/
    /**
    * Checks the Data Phase and calls user Endpoint handler.
    *
    * @param	InstancePtr is a pointer to the XUsbPsu instance.
    * @param	Event is a pointer to the Endpoint event occured in core.
    *
    * @return	None.
    *
    * @note		None.
    *
    *****************************************************************************/
    void XUsbPsu_EpXferComplete(struct XUsbPsu *InstancePtr,
                  const struct XUsbPsu_Event_Epevt *Event)
    {
      struct XUsbPsu_Ep	*Ept;
      struct XUsbPsu_Trb	*TrbPtr;
      u32	Length;
      u32	Epnum;
      u8	Dir;

      Xil_AssertVoid(InstancePtr != NULL);
      Xil_AssertVoid(Event != NULL);

      Epnum = Event->Epnumber;
      Ept = &InstancePtr->eps[Epnum];
      Dir = Ept->Direction;
      TrbPtr = &Ept->EpTrb[Ept->TrbDequeue]; // ? FIFO? Ept->TrbDequeue++; in next few lines
      Xil_AssertVoid(TrbPtr != NULL);

      Ept->TrbDequeue++;
      if (Ept->TrbDequeue == NO_OF_TRB_PER_EP) {
        Ept->TrbDequeue = 0U;
      }

      if (InstancePtr->ConfigPtr->IsCacheCoherent == (u8)0U) {
        Xil_DCacheInvalidateRange((INTPTR)TrbPtr, sizeof(struct XUsbPsu_Trb));
      }

      if (Event->Endpoint_Event == XUSBPSU_DEPEVT_XFERCOMPLETE) {
        Ept->EpStatus &= ~(XUSBPSU_EP_BUSY);
        Ept->ResourceIndex = 0U;
      }

      // Size of TRB
      Length = TrbPtr->Size & XUSBPSU_TRB_SIZE_MASK;

      if (Length == 0U) {
        Ept->BytesTxed = Ept->RequestedBytes;
      } else {
        if (Dir == XUSBPSU_EP_DIR_IN) {
          Ept->BytesTxed = Ept->RequestedBytes - Length;
        } else {
          if (Ept->UnalignedTx == 1U) {
            Ept->BytesTxed = (u32)roundup(Ept->RequestedBytes,
                            (u16)Ept->MaxSize);
            Ept->BytesTxed -= Length;
            Ept->UnalignedTx = 0U;
          } else {
            /*
            * Get the actual number of bytes transmitted
            * by host
            */
            Ept->BytesTxed = Ept->RequestedBytes - Length;
          }
        }
      }

      if (Dir == XUSBPSU_EP_DIR_OUT) {
        /* Invalidate Cache */
        if (InstancePtr->ConfigPtr->IsCacheCoherent == (u8)0U) {
          Xil_DCacheInvalidateRange((INTPTR)Ept->BufferPtr, Ept->BytesTxed);
        }
      }

      // call Handler e.g. BulkInHandler
      if (Ept->Handler) {
        Ept->Handler(InstancePtr->AppData, Ept->RequestedBytes, Ept->BytesTxed);
      }
    }
    ```

##### Low-level

* `XUsbPsu_ReadReg(InstancePtr, Offset)`
  * = `Xil_In32((InstancePtr)->ConfigPtr->BaseAddress + (u32)(Offset))`
  * return `uint32_t``

#### ATC Design

##### Firmware

* BulkOutHandler()
  * `EpBufferSend(InstancePtr->PrivateData, 2,(u8 *)(intptr_t(gpst_rd_ddr_img_info->ps_cur_rd_base_addr + img_data_offset) ,gst_img_cfg_info.img_actual_end_addr_offset);`
    * gpst_rd_ddr_img_info contains image pointer?
    * gst_img_cfg_info contains image length?

```c
void BulkOutHandler(void *CallBackRef, u32 RequestedBytes,
                            u32 BytesTxed)
{
    struct Usb_DevData *InstancePtr = CallBackRef;
    static u32 img_data_offset = 0;
    g_usb_rcv_flag = TRUE;
    u32  ddr_invalid_addr = 0;
    handle_usb_cmd();
    // ? Phase never used, never enter this, but BulkInHandler rely on RecvFlag
    if (Phase == USB_EP_STATE_COMMAND)
    {
        RecvFlag = 1;
    }
    // g_usb_snd_flag determined in handle_usb_cmd()
    if (g_usb_snd_flag)
    {
        //EpBufferSend(InstancePtr->PrivateData, 1, (void *)(u32 *)0x6400000, 1024*1024*2);
        if (g_usb_snd_otf_img_flag)
        {
            Xil_DCacheInvalidateRange(gst_rd_ddr_img_info.ps_cur_rd_base_addr + img_data_offset, gst_img_cfg_info.img_actual_end_addr_offset);
            EpBufferSend(InstancePtr->PrivateData, 1,(u8 *)(gst_rd_ddr_img_info.ps_cur_rd_base_addr + img_data_offset)\
                           ,gst_img_cfg_info.img_actual_end_addr_offset);
            g_usb_snd_otf_img_flag = 0;
            process_img_data(&gst_img_cfg_info,&gst_rd_ddr_img_info);
        }
        else if (g_usb_snd_img_flag)
        {
            ddr_invalid_addr = (u32)(gst_img_snd_pkt.p_img_snd_pointer);
            if (0 != ((u32)(gst_img_snd_pkt.p_img_snd_pointer) & 0x1f))
            {
                ddr_invalid_addr = (((u32)(gst_img_snd_pkt.p_img_snd_pointer) >> 5) | 0x01) << 5;
            }
            Xil_DCacheInvalidateRange(ddr_invalid_addr,gst_img_snd_pkt.img_snd_len + 64);
            EpBufferSend(InstancePtr->PrivateData, 1,gst_img_snd_pkt.p_img_snd_pointer\
                           ,gst_img_snd_pkt.img_snd_len);
            g_usb_snd_img_flag = 0;
            if (gst_img_snd_pkt.last_pkt_flag)
            {
                gst_rd_ddr_img_info.ps_rd_img_valid_flag = 0;
                Xil_Out32(gst_rd_ddr_img_info.ps_cur_rd_base_addr,0x00);
                Xil_DCacheFlushLine(gst_rd_ddr_img_info.ps_cur_rd_base_addr);
            }
        }
        else
        {
          EpBufferSend(InstancePtr->PrivateData, 1, (void *)&gst_tx_pkt, HEADER_LEN + gst_tx_pkt.payload_len);
        }
    }
}

// ? Always do nothing?
void BulkInHandler(void *CallBackRef, u32 RequestedBytes,
                           u32 BytesTxed)
{
    struct Usb_DevData *InstancePtr = CallBackRef;
   // if (g_usb_snd_flag)
    {
        //EpBufferSend(InstancePtr->PrivateData, 1, (void *)(u32 *)0x6400000, 1024*1024*2);
        //EpBufferSend(InstancePtr->PrivateData, 1, (void *)&gst_tx_pkt, 6 + gst_tx_pkt.payload_len);
    }

    if (RecvFlag == 1)
    {
       EpBufferRecv(InstancePtr->PrivateData, 1, (u8*)&gst_rx_pkt,1024);
       RecvFlag = 0;
    }


}
```

* void handle_usb_cmd(void)
  * This function is process the usb command
  * match the command, store in p_sub_fun_table, then execute
  * received data: pst_rx_pkt; data to be sent: pst_tx_pkt

  * pst_rx_pkt:
    * gst_rx_pkt.pkt_type
      * only respond to SET_PKT_TYPE / GET_PKT_TYPE / LOOP_BACK_PKT_TYPE
    * gst_rx_pkt.st_cmd_id.cmd_id: function table index
    * gst_rx_pkt.st_cmd_id.sub_id: sub table index
    * e.g. 0x04(pkt_type), 0x0005(sub), 0x0000(function) -> board_id

  * execute the command:
  * `err_code = p_sub_fun_table[gst_rx_pkt.st_cmd_id.sub_id].fun_name((st_cmd_pkt_t *)&gst_rx_pkt,(st_cmd_pkt_t *)&gst_tx_pkt);`

  * g_usb_snd_flag = TRUE; g_usb_rcv_flag = FALSE


```c
u16 fw_info(const st_cmd_pkt_t *pst_rx_pkt,st_cmd_pkt_t *pst_tx_pkt)
{
  u16 err_code = SUCCESS;
  Xil_AssertNonvoid(NULL != pst_tx_pkt);

   *(u32 *)&(pst_tx_pkt->payload_data[0]) = PS_FW_VER;
   *(u32 *)&(pst_tx_pkt->payload_data[4]) = PS_FW_DATE;
   *(u32 *)&(pst_tx_pkt->payload_data[8]) = Xil_In32(MISC_PL_VER_ADDR);
   *(u32 *)&(pst_tx_pkt->payload_data[12]) = Xil_In32(MISC_PL_DATE_ADDR);
   *(u32 *)&(pst_tx_pkt->payload_data[16]) = Xil_In32(SNR_CFG_IP_VER_ADDR);
   *(u32 *)&(pst_tx_pkt->payload_data[20]) = Xil_In32(SNR_CFG_IP_DATE_ADDR);
   *(u32 *)&(pst_tx_pkt->payload_data[24]) = Xil_In32(DPHY_IP_VER_ADDR);
   *(u32 *)&(pst_tx_pkt->payload_data[28]) = Xil_In32(DPHY_IP_DATE_ADDR);
   *(u32 *)&(pst_tx_pkt->payload_data[32]) = Xil_In32(IMG_IP_VER_ADDR);
   *(u32 *)&(pst_tx_pkt->payload_data[36]) = Xil_In32(IMG_IP_DATE_ADDR);
   pst_tx_pkt->payload_len = 40;
  return err_code;
}
```

* `u16 img_read_img(const st_cmd_pkt_t *pst_rx_pkt,st_cmd_pkt_t *pst_tx_pkt)` in `cmd_funs.c`
  * read command from `pst_rx_pkt`
    * img_read_flag, img_offset, rd_img_data_size
  * put something into `gst_img_snd_pkt`
    * p_img_snd_pointer, size, img_read_flag
      * `p_img_snd_pointer` is assigned to `gst_rd_ddr_img_info` (DDR?)
    * ```c
      typedef struct
      {
        u32  img_snd_len;
        u8   last_pkt_flag;
        u8   *p_img_snd_pointer;
      }st_img_snd_t;
      ```
  * if g_usb_snd_img_flag = true, DCacheInvalidateRange & EpBufferSend `gst_img_snd_pkt`

* `u16 read_ddr_img_data(const st_img_cfg_info_t *pst_img_cfg_info,volatile st_rd_ddr_img_info_t *const pst_rd_ddr_img_info)`
  * is done in main loop
  * if (gb_start_grab_flag && !(gb_start_transfer_flag && gpst_rd_ddr_img_info->ps_rd_img_valid_flag))
  * read index from IMG_WR_BUF_INDEX_STA_ADDR -> union_wr_img_buf_info
  * write to pst_rd_ddr_img_info
    * `gst_img_cfg_info` is passed in main loop, which is used in BulkOutHandler
    * should be some info only e.g. length

* `u16 sw_trig(const st_cmd_pkt_t *pst_rx_pkt,st_cmd_pkt_t *pst_tx_pkt)`
  * check if in Trig Mode and in SW Trig Mode
    * by reading IMG_MODE_ADDR and IMG_TRIG_MODE_ADDR
  * if yes, set IMG_SW_TRIG_ADDR

#### Host side program: MIGLibGen2_Debug

* DetectDevice
  * GUID has to be matched with driver

* `WUGD_WriteBulkData()`
  * param: buffer, length, datawritten
  * e.g. 04 00 05 00 00 00 00 00 01

* `ReceiveImageData()`
  * ultimately call `WUGD_ReadBulkData()`

* `MIGRequestReadFrameImag()`
  * Simply call `ReceiveImageData()` and do mutex things
* `MIGReadFirstFrameImage()`
  * send `{0x01,0x00}` before receiving image, all others is the same as `MIGRequestReadFrameImag()`

* `MIGGetImageDataFastMode()`
  * calculate no. of packets to be sent (`stImgReadPara.unImgSndTimes`) and size of the last packet (`stImgReadPara.unImgSndLastPktLen`) by dividing size of image size (`unImgActualSize`) to packet size (`unOnePktSize`)
    * ? `UINT unOnePktSize = 1024 * 1024 * 4`, why?
  * call `MIGReadFirstFrameImage()` to read 1st image;  
    `MIGRequestReadFrameImag()` to read remaining

* `MIGGetImageDataFastModeDualUSB()`
  * handled by 2 threads: `ReadImageDataProc`, `ReadDualImageDataProc`

* `void CSnrBImgDlg::OnTimer(UINT_PTR nIDEvent)`
  * do `MIGGetImageDataSWTrigger` or `MIGGetImageData`

### Misc.

* `Xil_DCacheInvalidateRange()`
  * mark cache line as invalid, obtain from memory next time 
  * requires if DMA / modified by 2nd processor
* `Xil_DCacheFlushLine()`

### Problems

#### Stuck at CDPLE p14,#0xa,c13,c13,c13,#5

_[arm Community](https://community.arm.com/developer/tools-software/tools/f/armds-forum/4579/disassembly-view-ds-5)_

* Debugger connection -> Try power cycle the board

> the binary code for "CDPLE p14,#0xa,c13,c13,c13,#5" is 0xdeaddead". I think this means the serial (or parallel?) communications trouble with the debugger. That is, instruction codes on the memory could not be fetched successfully. Please check your debugger connection.

### ZCU102

#### UART over USB

* CP2108
  * 1 to 4
  * up to 2Mbps
* UART0 & UART1
  * baud rate setting
  <!-- TODO -->

#### Problem: once boot, all light flashes

* Press `ENET RESET`

### 

IO 
