# Trust me, I'm an engineer

* Analysis + Simulation + Experiment -> precise
  * Not one less

* estimation! if rules conflict with each other/actual situation
  * part of analysis
  * use your own knowledge, don't self-bounded with rules
  * after modification is it imporved? worsen?
  * Simulation is for much later stage
  * 70% precise estimation + design margin
    * 100% precise is impossible <- component variaton + workmanship variaton + change in requirement

* Design
  * Level 1. Working
  * Level 2. Good Performance

* Trust me, I'm a mathematican
  * [List of mathematical symbols](https://en.wikipedia.org/wiki/List_of_mathematical_symbols)
  * := := definition / assignment
  * <=> := material equivalence, if and only if
  * => := material implication, if… then…
  * |= := ⊧ entailment
  * |= := ⊢ inference, x ⊢ y => y is derivable from x

* Good for Project Management
  * commitment & decision
  * 

* Rule of thumb
  * put version number in every design file
  * 
  * > 10% of your code should be comments

## Debug

* The most important test cases are 0, 1, 2
  * try input with 0, 1, 2

### Case study

* Xilinx HLS: U3OA GPI
  * Aim: "U3OA GPI" originally had 2 functions, debouncing 3 input GPI signals, and selecting trig_in based on a signal. However, the 2nd function was not required and wanted to be deleted. Also to make things more modular, I would like to cut 3 input signals to 1, and declare 3 "U3OA GPI" blocks in upper layer.
  * Mistake: Originally there's 3 input, so there're 3 debounce_cnt, but forgot to modify the following code later on:

    ``` c++
    ap_uint<C_REG_DEBOUNCE_LEN> g_debounce_cnt[C_GPI_NUM] = {};
    ...
    for (int i = 0; i < C_GPI_NUM; i++) {
    #pragma HLS UNROLL
        g_debounce_cnt[i] = debounce_cnt[i];
    }
    ```

  * Debug process:
    1. on hardware, found that debounce does not work once enabled
    2. stucked
    3. accidentially found that reg_debounce = 1 actually work
    4. found that debounce does not work once reg_debounce set to 9 (0-8 is working)
    5. modified the HLS C testbench: test for reg_debounce = 9, and found the bug mentioned above
  
  * What can be improved:
    * Should compare the original code and modified code

### Issue from appl

1. get to know their issue
2. get to know their system config
3. test our own Vision system
   * test each module individually, all have internal tools to test
     * e.g. to test OTF, use line scan interface board to simulate ext. trigger
4. check if interface with other system is correct

## Project Design

### Stage

* POC: critical parameter
  * POC first or design first?
    * is POC high risk? e.g. sensor that no one used before?
    * can someone do POC for you? ATC?
    * would POC spend too much time, equals to implementation real design?
