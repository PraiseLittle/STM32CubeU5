### DCACHE Component Diagram

```{uml}
@startuml
<style>
componentDiagram {
   arrow {
      FontSize 8
   }
}
</style>

title DCACHE Software Component Diagram

package "HAL" {
    [HAL_SERVICE]
    [HAL_DCACHE]
}

package "Low Layer" {
    [LL_DCACHE]
    [CMSIS]
    [DCACHE Interrupt Service Routine]
}

package "HW" {
    [STM32_HW]
}

[Appli] --> [HAL_DCACHE] : HAL DCACHE APIs
[Appli] <-- [HAL_DCACHE] : HAL DCACHE callbacks
[HAL_DCACHE] --> [LL_DCACHE] : LL DCACHE APIs
[HAL_DCACHE] -l-> [HAL_SERVICE] : HAL_GetTick
[HAL_DCACHE] <-- [DCACHE Interrupt Service Routine]
[LL_DCACHE] --> [CMSIS]:DCACHE registers definition
[STM32_HW] -u--> [DCACHE Interrupt Service Routine]: DCACHEx IRQ
[STM32_HW] <-u-- [LL_DCACHE] : DCACHE registers R/W
@enduml
```