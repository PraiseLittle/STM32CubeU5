### CRC Component Diagram

```{uml}
@startuml
<style>
componentDiagram {
   arrow {
      FontSize 8
   }
}
</style>

title CRC Software Component Diagram

package "HAL" {
    [HAL_CRC]

}

package "Low Layer" {
    [LL_CRC]
    [CMSIS device]
}

package "HW" {
    [STM32_HW]
}

[Appli] --> [HAL_CRC] : HAL CRC API
[HAL_CRC] --> [LL_CRC] : LL CRC API
[LL_CRC] --> [CMSIS device]:CRC register def
[LL_CRC] --> [STM32_HW]: CRC registers R/W
@enduml
```