# Heading

## Sub-heading

### Another deeper heading

Paragraphs are separated
by a blank line.

Two spaces at the end of a line leave a  
line break.

Text attributes _italic_, *italic*, __bold__, **bold**, `monospace`, ~~strikethrough~~.

Horizontal rule:

---

Bullet list:

* apples
* oranges
* pears

Numbered list:

  1. apples
  2. oranges
  3. pears

A [link](http://example.com).

A [link to heading](#Sub-heading)

![Nano Shinonome](https://vignette.wikia.nocookie.net/nichijou/images/7/79/Nanokey.png)

## UML: PlantUML plugin

* Filename extension: `.wsd`

```plantuml
@startuml

'single line comment'
' single line comment
/' multi-line
comment '/

skinparam backgroundColor #EEEBDC
skinparam handwritten true
actor Customer
Customer -> "login()" : Centre \n aligned
"login()" -> Customer : Left \l aligned
activate "login()"
Customer -> "placeOrder()" : Right \r aligned
"placeOrder()" -> Customer : ok
Customer -> "logout()"
"logout()" -> Customer : ok
deactivate "login()"

@enduml
```

* [Gantt Diagram - PlantUML](https://plantuml.com/gantt-diagram)

### Component Diagram

* [Component Diagram - PlantUML](https://plantuml.com/component-diagram)

```plantuml
@startuml
[First component]
[Another component] as Comp2  
component Comp3
component [Last\ncomponent] as Comp4
@enduml
```

### State diagram

```plantuml
@startuml
scale 600 width

title State diagram

'no space in states' name, use _ instead'
[*] -> State1
State1 --> State2 : Succeeded
State1 --> [*] : Aborted
State2 --> State3 : Succeeded
State2 --> [*] : Aborted
state State3 {
  state "Accumulate Enough Data\nLong State Name" as long1
  long1 : Just a test
  [*] --> long1
  long1 --> long1 : New Data
  long1 --> ProcessData : Enough Data
}
State3 --> State3 : Failed
State3 --> [*] : Succeeded / Save Result
State3 --> [*] : Aborted
@enduml
```

### Flow (Activity) diagram

  * [New Activity Diagram Beta syntax and features](https://plantuml.com/activity-diagram-beta)

```plantuml
@startuml

|Pipe 1|
start

:ClickServlet.handleRequest();
:new page;
if (Page.onSecurityCheck) then (true)
  :Page.onInit();
  if (isForward?) then (no)
	:Process controls;
	if (continue processing?) then (no)
	  stop
	endif
	
	if (isPost?) then (yes)
	  :Page.onPost();
	else (no)
	  :Page.onGet();
	endif
	:Page.onRender();
  endif
else (false)
endif

if (do redirect?) then (yes)
|Pipe 2|
  :redirect process;
  
|Pipe 1|
else
  if (do forward?) then (yes)
	:Forward request;
  else (no)
	:Render page template;
  endif
endif

stop

@enduml
```

### Timing diagram

* [Timing Diagram -PlantUML](https://plantuml.com/timing-diagram)

```plantuml

title chronological order

@startuml
robust "Web Browser" as WB
concise "Web User" as WU

@0
WU is Idle
WB is Idle

@100
WU is Waiting
WB is Processing

@300
WB is Waiting
@enduml
```

```plantuml
@startuml

title by participant

concise "Client" as Client
concise "Server" as Server
robust "Response freshness" as Cache

Server is idle
Client is idle
'from top to bottom
Cache has stale,fresh

@Client
0 is send
Client -> Server@+25 : GET
+25 is await
+75 is recv
+25 is idle
+25 is send
Client -> Server@+25 : GET\nIf-Modified-Since: 150
+25 is await
+50 is recv
+25 is idle
@100 <-> @275 : no need to re-request from server

@Server
25 is recv
+25 is work
+25 is send
Server -> Client@+25 : 200 OK\nExpires: 275
+25 is {-}
+75 is recv
+25 is send
Server -> Client@+25 : 304 Not Modified
+25 is idle

@Cache
75 is fresh
+200 is stale
+25 is {fresh,stale}
@enduml
```
