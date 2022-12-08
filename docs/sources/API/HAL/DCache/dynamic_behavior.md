### HAL DCACHE Finite State Machine
```{uml}
@startuml

<style>
stateDiagram {
'LineColor Gray
arrow {
FontSize 13
LineColor Blue
}
}
</style>

state PROCESSING  {

state "global_state = IDLE" as state2 #5499C7

state2 -down-> state2 : HAL_DCACHE_SetReadBurstType,\nHAL_DCACHE_RegisterErrorCallback,\nHAL_DCACHE_RegisterInvalidateCompleteCallback,\nHAL_DCACHE_RegisterCleanByAddrCallback,\nHAL_DCACHE_RegisterInvalidateByAddrCallback,\n   HAL_DCACHE_RegisterCleanInvalidByAddrCallback

state "global_state = ACTIVE" as state3 #33FF3C

state2 --> state3 : HAL_DCACHE_Start
state3 -up-> state2 : HAL_DCACHE_Stop
state3 -right-> state3 : HAL_DCACHE_RegisterInvalidateCompleteCallback,\nHAL_DCACHE_RegisterCleanByAddrCallback,\nHAL_DCACHE_RegisterInvalidateByAddrCallback,\n   HAL_DCACHE_RegisterCleanInvalidByAddrCallback,\nHAL_DCACHE_IRQHandler

state "global_state = MAINTENANCE" as state4 #FF33EC

state3 --> state4 : HAL_DCACHE_Invalidate,\n HAL_DCACHE_Invalidate_IT,\n HAL_DCACHE_CleanByAddr,\n HAL_DCACHE_CleanByAddr_IT,\n HAL_DCACHE_InvalidateByAddr,\n HAL_DCACHE_InvalidateByAddr_IT,\n HAL_DCACHE_CleanInvalidbyAddr,\n HAL_DCACHE_CleanInvalidbyAddr_IT
state4 --> state3 : Maintenance Operations Finished,\nHAL_DCACHE_IRQHandler in IT mode
state4 -up-> state2 : HAL_DCACHE_Stop

PROCESSING --> PROCESSING : HAL_DCACHE_EnableMonitors\nHAL_DCACHE_DisableMonitors\nHAL_DCACHE_ResetMonitors\nHAL_DCACHE_GetMonitorReadHitValue\nHAL_DCACHE_GetMonitorReadMissValue\nHAL_DCACHE_GetMonitorWriteHitValue\nHAL_DCACHE_GetMonitorWriteMissValue\nHAL_DCACHE_GetReadBurstType\nHAL_DCACHE_GetState

}

[*] --> state2 : HAL_DCACHE_Init 
PROCESSING -u-> [*] : HAL_DCACHE_DeInit

@enduml
```
<br>

### HAL DCACHE Sequence Diagrams

#### HAL DCACHE Maintenance Operations in Polling mode:
```{uml}
@startuml

skinparam sequenceMessageAlign center

"User Application"->"Driver DCACHE" : HAL_DCACHE_Init
"Driver DCACHE"-->"Driver RCC" : Compilation switch: clock activation
rnote over "Driver DCACHE"
Invalidate Operation by Hardware
endrnote
"Driver DCACHE" --> "User Application" : return HAL_OK

group Loop [Can be repeated]

group Optional
"User Application"->"Driver DCACHE" : HAL_DCACHE_SetReadBurstType
"Driver DCACHE" --> "User Application" : return HAL_OK
end

group Optional
"User Application"->"Driver DCACHE" : HAL_DCACHE_EnableMonitors
"Driver DCACHE" --> "User Application" : return HAL_OK
end

"User Application"->"Driver DCACHE" : HAL_DCACHE_Start(HAL_DCACHE_IT_NONE)
"Driver DCACHE" --> "User Application" : return HAL_OK

group Loop [Can be repeated]

"User Application"->"Driver DCACHE" : HAL_DCACHE_Invalidate,\nHAL_DCACHE_CleanByAddr,\nHAL_DCACHE_InvalidateByAddr,\nHAL_DCACHE_CleanInvalidByAddr


rnote over "Driver DCACHE"
Check Busy flags: Flags = 0
endrnote

rnote over "Driver DCACHE"
Operation ended successfully
endrnote

"Driver DCACHE" --> "User Application" : return HAL_OK

else Busy

"User Application"->"Driver DCACHE" : HAL_DCACHE_Invalidate,\nHAL_DCACHE_CleanByAddr,\nHAL_DCACHE_InvalidateByAddr,\nHAL_DCACHE_CleanInvalidByAddr

rnote over "Driver DCACHE"
Check Busy flags: Flags = 1
endrnote

rnote over "Driver DCACHE"
DCACHE driver busy with another ongoing operation
endrnote

"Driver DCACHE" --> "User Application" : return HAL_BUSY

else Error

"User Application"->"Driver DCACHE" : HAL_DCACHE_Invalidate,\nHAL_DCACHE_CleanByAddr,\nHAL_DCACHE_InvalidateByAddr,\nHAL_DCACHE_CleanInvalidByAddr

rnote over "Driver DCACHE"
Check Busy flags: Flags = 0
endrnote

rnote over "Driver DCACHE"
Elapsed Timeout 600ms: Operation completed with error
endrnote

"Driver DCACHE" --> "User Application" : return HAL_ERROR

end

group Optional
"User Application"->"Driver DCACHE" : HAL_DCACHE_GetMonitorReadHitValue, HAL_DCACHE_GetMonitorReadMissValue,\nHAL_DCACHE_GetMonitorWriteHitValue, HAL_DCACHE_GetMonitorWriteMissValue
"Driver DCACHE" --> "User Application"

"User Application"->"Driver DCACHE" : HAL_DCACHE_ResetMonitors
"Driver DCACHE" --> "User Application" : return HAL_OK
end

"User Application"->"Driver DCACHE" : HAL_DCACHE_Stop
"Driver DCACHE" --> "User Application" : return HAL_OK

end

"User Application"->"Driver DCACHE" : HAL_DCACHE_DeInit
"Driver DCACHE" --> "User Application"

@enduml
```

<br>

#### HAL DCACHE Maintenance Operations in Polling mode with Error Interrupt enabled (Clean operation error):

```{uml}
@startuml

skinparam sequenceMessageAlign center

== DCACHE Initialization ==

rnote over "User Application"
The user can choose Option 1 or Option 2 or nothing.
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"User Application" ->  "Driver DCACHE" : HAL_DCACHE_RegisterErrorCallback(myDCACHE_ErrorCallback)
"Driver DCACHE" --> "User Application" : return HAL_OK
end

"User Application"->"Driver DCACHE" : HAL_DCACHE_Start(HAL_DCACHE_IT_ERROR)

rnote over "Driver DCACHE"
Flag Error Interrupt enabled
endrnote

"Driver DCACHE" --> "User Application" : return HAL_OK

"User Application"-[#Blue]>"Driver DCACHE" : HAL_DCACHE_CleanByAddr or\nHAL_DCACHE_CleanInvalidByAddr

activate "Driver DCACHE" #Blue

rnote over "Driver DCACHE"
Check Busy flags: Flags = 0
endrnote

"DCACHE_IRQHandler" <[#Orange]- : DCACHE Error interrupt

activate "Driver DCACHE" #Orange

"DCACHE_IRQHandler" -[#Orange]> "Driver DCACHE" : HAL_DCACHE_IRQHandler

rnote over "Driver DCACHE"
Flag Error Interrupt = 1 --> Error in Clean operation
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"Driver DCACHE" -[#Orange]> "User Application" : myDCACHE_ErrorCallback(HAL_DCACHE_ERROR_EVICTION_CLEAN)
"User Application" -[#Orange]-> "Driver DCACHE"
end 
group Option 2 [USE OVERRIDEN WEAK CALLBACKS]
"Driver DCACHE" -[#Orange]> "User Application" : HAL_DCACHE_ErrorCallback(HAL_DCACHE_ERROR_EVICTION_CLEAN)
"User Application" -[#Orange]-> "Driver DCACHE"
deactivate "Driver DCACHE"
end
"Driver DCACHE" -[#Blue]-> "User Application" : return HAL_OK
deactivate "Driver DCACHE"
rnote over "User Application"
The user can call HAL_DCACHE_Stop() to disable the Error Interrupt 
             and stop the DCACHE or make an other action.
endrnote
@enduml
```

<br>

#### HAL DCACHE in Polling mode or Interrupt mode with Error Interrupt enabled (Eviction error):

```{uml}
@startuml

skinparam sequenceMessageAlign center

== DCACHE Initialization ==

rnote over "User Application"
The user can choose Option 1 or Option 2 or nothing.
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"User Application" ->  "Driver DCACHE" : HAL_DCACHE_RegisterErrorCallback(myDCACHE_ErrorCallback)
"Driver DCACHE" --> "User Application" : return HAL_OK
end

"User Application"->"Driver DCACHE" : HAL_DCACHE_Start(HAL_DCACHE_IT_ERROR)

rnote over "Driver DCACHE"
Flag Error Interrupt enabled
endrnote

"Driver DCACHE" --> "User Application" : return HAL_OK

"DCACHE_IRQHandler" <- : DCACHE Error interrupt

"DCACHE_IRQHandler" -> "Driver DCACHE" : HAL_DCACHE_IRQHandler

rnote over "Driver DCACHE"
Flag Error Interrupt = 1 --> Eviction Error
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"Driver DCACHE" -> "User Application" : myDCACHE_ErrorCallback(HAL_DCACHE_ERROR_EVICTION_CLEAN)
"User Application" --> "Driver DCACHE"
end

group Option 2 [USE OVERRIDEN WEAK CALLBACKS]
"Driver DCACHE" -> "User Application" : HAL_DCACHE_ErrorCallback(HAL_DCACHE_ERROR_EVICTION_CLEAN)
"User Application" --> "Driver DCACHE"
end

rnote over "User Application"
The user can call HAL_DCACHE_Stop() to disable the Error Interrupt 
             and stop the DCACHE or make an other action.
endrnote

@enduml
```

<br>

#### HAL DCACHE Maintenance Operations in Interrupt mode:

```{uml}
@startuml

skinparam sequenceMessageAlign center

== DCACHE Initialization ==

rnote over "User Application"
The user can choose Option 1 or Option 2 or nothing.
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"User Application" ->  "Driver DCACHE" : HAL_DCACHE_RegisterCleanByAddrCallback(myDCACHE_CleanByAddrCallback),\nHAL_DCACHE_RegisterInvalidateByAddrCallback(myDCACHE_InvalidateByAddrCallback),\nHAL_DCACHE_RegisterInvalidateCompleteCallback(myDCACHE_InvalidateCompleteCallback),\nHAL_DCACHE_RegisterCleanInvalidByAddrCallback(myDCACHE_CleanInvalidByAddrCallback)
"Driver DCACHE" --> "User Application" : return HAL_OK
end

"User Application"->"Driver DCACHE" : HAL_DCACHE_Start (HAL_DCACHE_IT_NONE)
"Driver DCACHE" --> "User Application" : return HAL_OK

group Loop [Can be repeated]
"User Application"->"Driver DCACHE" : HAL_DCACHE_CleanByAddr_IT,\nHAL_DCACHE_InvalidateByAddr_IT,\nHAL_DCACHE_CleanInvalidByAddr_IT,\nHAL_DCACHE_Invalidate_IT

rnote over "Driver DCACHE"
Check Busy flags: Flags = 0
endrnote

rnote over "Driver DCACHE"
Flag Command Interrupt (CMDENDIE) enabled or
    Flag Invalidate Interrupt (BSYENDIE) enabled
endrnote

"Driver DCACHE" --> "User Application" : return HAL_OK

"DCACHE_IRQHandler" <- : DCACHE Maintenance interrupt

"DCACHE_IRQHandler" -> "Driver DCACHE" : HAL_DCACHE_IRQHandler

rnote over "Driver DCACHE"
Flag Command Interrupt (CMDENDIE) disabled or
    Flag Invalidate Interrupt (BSYENDIE) disabled
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"Driver DCACHE" -> "User Application" : myDCACHE_CleanByAddrCallback,\nmyDCACHE_InvalidateByAddrCallback,\nmyDCACHE_InvalidateCompleteCallback,\nmyDCACHE_CleanInvalidByAddrCallback
"User Application" --> "Driver DCACHE"
end

group Option 2 [USE OVERRIDEN WEAK CALLBACKS]
"Driver DCACHE" -> "User Application" : HAL_DCACHE_CleanByAddrCallback,\nHAL_DCACHE_InvalidateByAddrCallback,\nHAL_DCACHE_InvalidateCompleteCallback,\nHAL_DCACHE_CleanInvalidByAddrCallback
"User Application" --> "Driver DCACHE"
end

end

rnote over "User Application"
The user can call HAL_DCACHE_Stop() to stop 
     the DCACHE or make an other action.
endrnote

@enduml
```

<br>

#### HAL DCACHE Maintenance Operations in Interrupt mode with Error Interrupt enabled (Clean operation error):

```{uml}
@startuml

skinparam sequenceMessageAlign center

== DCACHE Initialization ==

rnote over "User Application"
The user can choose Option 1 or Option 2 or nothing.
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"User Application" ->  "Driver DCACHE" : HAL_DCACHE_RegisterErrorCallback(myDCACHE_ErrorCallback)
"Driver DCACHE" --> "User Application" : return HAL_OK
end

"User Application"->"Driver DCACHE" : HAL_DCACHE_Start (HAL_DCACHE_IT_ERROR)

rnote over "Driver DCACHE"
Flag Error Interrupt enabled
endrnote

"Driver DCACHE" --> "User Application" : return HAL_OK

group Option 1 [USE REGISTER CALLBACKS]
"User Application" ->  "Driver DCACHE" : HAL_DCACHE_RegisterCleanByAddrCallback(myDCACHE_CleanByAddrCallback),\nHAL_DCACHE_RegisterCleanInvalidByAddrCallback(myDCACHE_CleanInvalidByAddrCallback)
"Driver DCACHE" --> "User Application" : return HAL_OK
end

"User Application"->"Driver DCACHE" : HAL_DCACHE_CleanByAddr_IT,\nHAL_DCACHE_CleanInvalidByAddr_IT

rnote over "Driver DCACHE"
Check Busy flags: Flags = 0
endrnote

rnote over "Driver DCACHE"
Flag Command Interrupt (CMDENDIE) enabled
endrnote

"Driver DCACHE" --> "User Application" : return HAL_OK

"DCACHE_IRQHandler" <- : DCACHE Error interrupt

"DCACHE_IRQHandler" -> "Driver DCACHE" : HAL_DCACHE_IRQHandler

rnote over "Driver DCACHE"
Flags Error Interrupt = 1 --> Error in Clean operation
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"Driver DCACHE" -> "User Application" : myDCACHE_ErrorCallback(HAL_DCACHE_ERROR_EVICTION_CLEAN)
"User Application" --> "Driver DCACHE"
end

group Option 2 [USE OVERRIDEN WEAK CALLBACKS]
"Driver DCACHE" -> "User Application" : HAL_DCACHE_ErrorCallback(HAL_DCACHE_ERROR_EVICTION_CLEAN)
"User Application" --> "Driver DCACHE"
end

"DCACHE_IRQHandler" <- : DCACHE Maintenance interrupt

"DCACHE_IRQHandler" -> "Driver DCACHE" : HAL_DCACHE_IRQHandler

rnote over "Driver DCACHE"
Flag Command Interrupt (CMDENDIE) disabled
endrnote

group Option 1 [USE REGISTER CALLBACKS]
"Driver DCACHE" -> "User Application" : myDCACHE_CleanByAddrCallback,\nmyDCACHE_CleanInvalidByAddrCallback
"User Application" --> "Driver DCACHE"
end

group Option 2 [USE OVERRIDEN WEAK CALLBACKS]
"Driver DCACHE" -> "User Application" :  HAL_DCACHE_CleanByAddrCallback,\nHAL_DCACHE_CleanInvalidByAddrCallback
"User Application" --> "Driver DCACHE"
end

rnote over "User Application"
The user can call HAL_DCACHE_Stop() to disable the Error Interrupt 
             and stop the DCACHE or make an other action.
endrnote

@enduml
```
