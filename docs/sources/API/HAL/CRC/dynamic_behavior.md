### CRC State Machine

#### Single process at a time

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

state "State 0" as state0
state0 :global_state = RESET

state "State 1" as state1
state1 :global_state = IDLE

state "State 2" as state2
state2 : global_state = ACTIVE

[*] -> state1 :HAL_CRC_Init
state1 --> state0 : HAL_CRC_DeInit
state0 --> state1 : HAL_CRC_Init

state1 -> state1 :HAL_CRC_SetConfig                           \n HAL_CRC_GetConfig                           \n HAL_CRC_ResetConfig                        \n HAL_CRC_SetConfigPolynomial         \n HAL_CRC_SetInputReverseMode        \n HAL_CRC_GetInputReverseMode       \n HAL_CRC_SetOutputReverseMode    \n HAL_CRC_GetOutputReverseMode   \n HAL_CRC_SetIndependentData        \n HAL_CRC_GetIndependentData       \n
state1 --> state2 : HAL_CRC_Calculate \n   HAL_CRC_Accumulate
state2 --> state1 : HAL_OK   

@enduml
```

### CRC Sequence Diagram

#### Use case 1: Starting a CRC calculation with default configuration

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" :  HAL_CRC_Calculate

note right: ** CRC calculating **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **

@enduml
```

#### Use case 2: Starting a CRC calculation with user configuration

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Configuration ==

"User Application"->"HAL CRC Driver" : HAL_CRC_SetConfig

note right: ** Global configuration **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" :HAL_CRC_Calculate    

note right: ** CRC calculating **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **

@enduml
```

#### Use case 3: Starting successive CRC calculations with the same user configuration

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Configuration ==

"User Application"->"HAL CRC Driver" : HAL_CRC_SetConfig

note right: ** Global configuration **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** 1rst CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

...
...
...
...
...

"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** nth CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **
@enduml
```

#### Use case 4: Starting a CRC calculation then continuing the calculation on new data

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Configuration ==

"User Application"->"HAL CRC Driver" : HAL_CRC_SetConfig

note right: ** Global configuration **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

"User Application"->"HAL CRC Driver" : HAL_CRC_Accumulate

note right: ** Continuing the previous CRC calculating with new data **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY
...
...
...
...
...

"User Application"->"HAL CRC Driver" : HAL_CRC_Accumulate

note right: ** nth CRC accumulating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **
@enduml
```

#### Use case 5: Starting successive CRC calculations with differents configurations

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Configuration ==

"User Application"->"HAL CRC Driver" : HAL_CRC_SetConfig

note right: ** 1rst Global configuration **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** 1rst CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

...
...
...
...
...
== Configuration ==
"User Application"->"HAL CRC Driver" : HAL_CRC_SetConfig

note right: ** nth Global configuration **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

== Process : Polling mode ==
"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** nth CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **
@enduml
```

#### Use case 6: Restoring the default configuration

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** 1rst CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

...
...
...
== Configuration ==
"User Application"->"HAL CRC Driver" : HAL_CRC_SetConfig

note right: ** Global configuration **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

== Process : Polling mode ==
"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** nth CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY
...
...
...
== Configuration ==
"User Application"->"HAL CRC Driver" : HAL_CRC_ResetConfig

note right: ** Restoring default global configuration**

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

== Process : Polling mode ==
"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** mth CRC calculating **

"HAL CRC Driver" --> "User Application": HAL_OK or HAL_INVALID_PARAM or HAL_BUSY
note right: ** return **
@enduml
```

#### Use case 7: Starting a CRC calculation with different polynomial configuration

```{uml}
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" :  HAL_CRC_Calculate

note right: ** 1rst CRC calculating **

"HAL CRC Driver" --> "User Application": hal status : HAL_INVALID_PARAM or HAL_BUSY

...
...
...
...
...

"User Application"->"HAL CRC Driver" : HAL_CRC_SetPolynomial

note right: ** Modifying the polynomial **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM

"User Application"->"HAL CRC Driver" : HAL_CRC_Calculate

note right: ** nth CRC calculating **

"HAL CRC Driver" --> "User Application": hal status : HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **
@enduml


## Use case 8: Deinitializing the CRC peripheral to start a new process
@startuml
' To add a number by line
'autonumber

' Fix order of each column
== Initialization ==

"User Application"->"System" : HAL_Init()

note right: **  Configure the Flash prefetch, the time base source and the NVIC **

"System" --> "User Application": hal status : HAL_OK or HAL_ERROR

note right: ** Return **

"User Application"->"System" : SystemClock_Config

note right: ** Configure system clock**

"System" --> "User Application"

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" :  HAL_CRC_Calculate

note right: ** CRC calculating **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **
== Deinitialization ==

"User Application"->"HAL CRC Driver" : HAL_CRC_DeInit()

note right: ** Deinitialize the CRC peripheral **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK

note right: ** Return **
== Initialization ==

"User Application"->"HAL CRC Driver" : HAL_CRC_Init()

note right: ** Initialize the CRC handle and associate an instance **

"HAL CRC Driver" --> "User Application" : hal status : HAL_OK or HAL_INVALID_PARAM

note right: ** Return **

== Process : Polling mode ==

"User Application"->"HAL CRC Driver" :  HAL_CRC_Calculate

note right: ** CRC new calculating **

"HAL CRC Driver" --> "User Application": hal status : HAL_OK or HAL_INVALID_PARAM or HAL_BUSY

note right: ** return **

@enduml
```

