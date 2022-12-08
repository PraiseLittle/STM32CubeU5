\page dynamic_behavior Dynamic behavior

The following section describes the dynamic behavior of the driver.

### PPP State Machine

#### Single process at a time

```{uml}
@startuml
<style>
stateDiagram {
   arrow {
      FontSize 9
      LineColor Black
   }
}
</style>
note "4 processes, 1 at a time and error management" as N1

state Initialized {
   state "State 1" as state1
   state1 : global_state = INIT

   state "State 2" as state2
   state2 : global_state = IDLE

   state "Processing" as process {
      state "State 3i" as state3i
      state3i : global_state = TX

      state "State 3j" as state3j
      state3j : global_state = RX

      state "State 3k" as state3k
      state3k : global_state = LISTEN

      state "State 4k1" as state4k1
      state4k1 : global_state = TX_LISTEN

      state "State 4k2" as state4k2
      state4k2 : global_state = RX_LISTEN
   }

   state "State 5" as state5
   state5 : global_state = ABORT
}

[*] -r-> state1 : HAL_PPP_Init
Initialized -l> [*] : HAL_PPP_DeInit
state1 -r-> state2 : HAL_PPP_SetConfig

state2 --> state2 :\
HAL_PPP_SetConfig/SetItem\n\
HAL_PPP_Enable/Disable/SetConfig/Feature\n\

state2 ---[#Blue]d-> state3j :\
<color #Blue>HAL_PPP_Receive/_IT/_DMA</color>\n\
<color #Blue>HAL_PPP_Receive/_IT/_DMA</color>\n\
<color #Blue>HAL_PPP_SeqReceive_DMA/IT</color>

state3j ----[#Green]u-> state2:\
<color #Green> Receive complete</color>

state2 ---[#Blue]d-> state3i :\
<color #Blue>HAL_PPP_Transmit/_IT/_DMA</color>\n\
<color #Blue>HAL_PPP_Transmit/_IT/_DMA</color>\n\
<color #Blue>HAL_PPP_SeqTransmit_DMA/IT</color>

state3i ----[#Green]u-> state2 :\
<color #Green>Transmit complete</color>

state2 ---d-> state3k : HAL_PPP_EnableListen_IT
state3k ---u-> state2 : HAL_PPP_DisableListen_IT

state3k ---[#Blue]d-> state4k1 :\
<color #Blue>HAL_PPP_SeqTransmit_DMA/IT</color>

state4k1 ---[#Green]u-> state3k :\
<color #Green>Transmit seq complete</color>

state3k ---[#Blue]d-> state4k2 :\
<color #Blue>HAL_PPP_SeqReceive_DMA/IT</color>

state4k2 ---[#Green]u-> state3k :\
<color #Green>Receive seq complete</color>

state4k1 ---[#Blue]l-> state4k2 :\
<color #Blue>HAL_PPP_SeqReceive_DMA/IT</color> 

state4k2 ---[#Blue]r-> state4k1 :\
<color #Blue>HAL_PPP_SeqTransmit_DMA/IT</color> 

process -[#Orange]-> state2:\
<color #Orange> Recoverable error</color>

process --> state5 : HAL_PPP_Abort

state5 -[#Orange]-> state2 :\
<color #Orange> Abort complete</color>
@enduml
```

#### Multi process can run in parallel

```{uml}
@startuml
<style>
stateDiagram {
   arrow {
      FontSize 10
      LineColor Blue
   }
}
</style>
note "2 processes, can run in parallel" as N1

state "State 0" as state0
state0 : global_state = RESET
state0 : process_i_state = RESET
state0 : process_j_state = RESET

state "State 1" as state1
state1 : global_state = INIT

state "IDLE" as idle {
   state "State 2" as state2
   state2 : global_state = IDLE
   state2 : process_i_state = IDLE
   state2 : process_j_state = IDLE

   state "State 2i" as state2i
   state2i : process_i_state = IDLE

   state "State 2j" as state2j
   state2j : process_j_state = IDLE

   state fork_state <<fork>>

   state "Processing i" as process_i {
      state "State 3i" as state3i
      state3i : process_i_state = PROCESS_I_STEP_1

      state "State 4i" as state4i
      state4i : process_i_state = PROCESS_I_STEP_n
   }

   state "State 5i" as state5i
   state5i : process_i_state = ABORT

   state "Processing j" as process_j {
      state "State 3j" as state3j
      state3j : process_j_state = PROCESS_J_STEP_1

      state "State 4j" as state4j
      state4j : process_j_state = PROCESS_J_STEP_n
   }

   state "State 5j" as state5j
   state5j : process_j_state = ABORT

   state join_state <<join>>
}

[*] --> state0
state0 --> state1 : HAL_PPP_Init
state1 --> state0 : HAL_PPP_DeInit
state1 --> state2 : HAL_PPP_SetConfig
state2 --> state2 : HAL_PPP_SetConfig\nHAL_PPP_SetItem
idle --> state0 : HAL_PPP_DeInit

state2 ---> fork_state
fork_state --> state2i
fork_state --> state2j

state2i --> state3i : HAL_PPP_process#i
state3i --> state4i : Process moves to next step
state4i --> state2i : Process i complete
state5i --> state2i : Process i ABORT complete
process_i --> state5i : HAL_PPP_Abort#i
process_i --> state1 : Non-recoverable error
process_i --> state2i : Recoverable error

state2j --> state3j : HAL_PPP_process#j
state3j --> state4j : Process moves to next step
state4j --> state2j : Process j complete
state5j --> state2j : Process j ABORT complete
process_j --> state5j : HAL_PPP_Abort#j
process_j --> state1 : Non-recoverable error
process_j --> state2j : Recoverable error

state2j --> join_state 
state2i --> join_state 
join_state --> state2

@enduml
```

#### One Single sub-instance active at a time

```{uml}
@startuml
<style>
stateDiagram {
   arrow {
      FontSize 10
      LineColor Blue
   }

}
</style>
note "2 sub-instances, 1 active at a time" as N1

state "State 0" as state0
state0 : global_state = RESET
state0 : i_state = RESET
state0 : j_state = RESET

   state "State 1" as state1
   state1 : global_state = INIT

state "IDLE" as idle {
   state "State 2" as state2
   state2 :global_state = IDLE


   state fork_state <<fork>>

   state "State 2i" as state2i
   state2i : i_state = RESET

   state "State 2j" as state2j
   state2j : j_state = RESET

   state "ACTIVE" as active {

      state "State 3i" as state3i
      state3i : i_state = IDLE

      state "State 3j" as state3j
      state3j : j_state = IDLE

      state "State 4i" as state4i
      state4i : i_state = ACTIVE

      state "State 4j" as state4j
      state4j : j_state = ACTIVE
   }
   state join_state <<join>>
}

[*] -> state0
state0 -> state1 : HAL_PPP_Init
state1 -> state0 : HAL_PPP_DeInit
state1 --> state2 : HAL_PPP_SetConfig
state2 -> state2 : HAL_PPP_SetConfig
idle -> state0 : HAL_PPP_DeInit

state2 --> fork_state
fork_state --> state2i
fork_state --> state2j

state2i ---> state3i : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{i)
state2j ---> state3j : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{j)

state3i ---> state4i : if (j_state != ACTIVE)\nHAL_PPP_{SubBlock}_Start(i) 
state3i ---> state3i : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{i)\nif (j_state != ACTIVE)\nHAL_PPP_{SubBlock}_SetConfig{i) 
state4i -u--> state3i : HAL_PPP_{SubBlock}_Stop(i)\nRecoverable error

state3j ---> state4j : if (j_state != ACTIVE)\nHAL_PPP_{SubBlock}_Start(j) 
state3j ---> state3j : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{j)\nif (i_state != ACTIVE)\nHAL_PPP_{SubBlock}_SetConfig{j) 
state4j -u--> state3j : HAL_PPP_{SubBlock}_Stop(j)\nRecoverable error

state2i -u-> join_state 
state2j -u-> join_state 
join_state -l> state2

active ----u> state1 : Non-recoverable error

@enduml
```

#### Multi sub-instances can run in parallel

```{uml}
@startuml
<style>
stateDiagram {
   arrow {
      FontSize 10
      LineColor Blue
   }
}
</style>
note "2 sub-instances, can run in parallel" as N1

state "State 0" as state0
state0 : global_state = RESET
state0 : i_state = RESET
state0 : j_state = RESET

   state "State 1" as state1
   state1 : global_state = INIT

state "IDLE" as idle {
   state "State 2" as state2
   state2 :global_state = IDLE


   state fork_state <<fork>>

   state "State 2i" as state2i
   state2i : i_state = RESET

   state "State 2j" as state2j
   state2j : j_state = RESET

   state "ACTIVE" as active {

      state "State 3i" as state3i
      state3i : i_state = IDLE

      state "State 3j" as state3j
      state3j : j_state = IDLE

      state "State 4i" as state4i
      state4i : i_state = ACTIVE

      state "State 4j" as state4j
      state4j : j_state = ACTIVE
   }
   state join_state <<join>>
}

[*] -> state0
state0 -> state1 : HAL_PPP_Init
state1 -> state0 : HAL_PPP_DeInit
state1 --> state2 : HAL_PPP_SetConfig
state2 -> state2 : HAL_PPP_SetConfig
idle -> state0 : HAL_PPP_DeInit

state2 --> fork_state
fork_state --> state2i
fork_state --> state2j

state2i ---> state3i : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{i)
state2j ---> state3j : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{j)

state3i ---> state4i : HAL_PPP_{SubBlock}_Start(i) 
state3i ---> state3i : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{i)\nif (j_state != ACTIVE)\nHAL_PPP_{SubBlock}_SetConfig{i) 
state4i -u--> state3i : HAL_PPP_{SubBlock}_Stop(i)\nRecoverable error

state3j ---> state4j : HAL_PPP_{SubBlock}_Start(j) 
state3j ---> state3j : HAL_PPP_{SubBlock}_SetConfig{SubInstance}{j)\nif (i_state != ACTIVE)\nHAL_PPP_{SubBlock}_SetConfig{j) 
state4j -u--> state3j : HAL_PPP_{SubBlock}_Stop(j)\nRecoverable error

state2i -u-> join_state 
state2j -u-> join_state 
join_state -l> state2

active ----u> state1 : Non-recoverable error

@enduml
```
### PPP Sequence Diagram

#### User application starting a driver

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
participant "User Application" as part1
participant "Driver PPP" as part2
participant "System" as part3

part1->part3 : HAL_Init()
part3 --> part1
part1->part3 : Configure system clock
part3 --> part1
part1->part2 : HAL_PPP_Init()
part2 --> part1
part1->part3 : PPP HW Initialisation (old MSPInit())
part3 --> part1
part1->part2 : HAL_PPP_SetConfig
part2 --> part1
@enduml
```

#### User application starting a DMA transfer
```{uml}
@startuml
"User Application"->"PPP Driver" : HAL_PPP_Xfer_DMA()
"PPP Driver"->"DMA Driver" : HAL_DMA_Start_IT
"ISR" -> "DMA Driver" : IRQ_HANDLER
"DMA HW" -> "ISR" : DMA_Xfer_Complete
"DMA Driver" -> "DMA Driver" : Clear IRQ
"DMA Driver" -> "PPP Driver" : Xfer_Complete
"PPP Driver" -> "PPP Driver": Clear Xfer_Complete
"PPP Driver" -> "User Application" : Xfer_Complete
@enduml
```
