\mainpage DCACHE Software Detailed Design

# 1.Description

**Title** : EmbSW_Cube2_IP_DCACHE_SDD

**Author** : A. JAGOT

**Version** : 1.0

**Document Reference**: [cx778559](https://codex.cro.st.com/plugins/docman/index.php?group_id=3244&id=778559&action=show)

*Based on template cx564179 version 2.0*

**Approval Table**

Project Role           | Name           | Date
---------------------- | -------------- | ----
Cube2 E03 SW PL        | P. LE CORRE    | 18-10-2022
Cube2 SW eQA           | C. ORSINI      | 18-10-2022

**Document history**

Date       | Author   | Version | Description
---------- | ------   | ------- | -----------
16-09-2022 | A. JAGOT | 1.0_P1  | Initial proposed version
30-09-2022 | A. JAGOT | 1.0_P2  | Second proposed version with updates: Introduction, Dependencies, HAL_DCACHE_DeInit/Start/Stop, Sequence diagrams, FSM
10-10-2022 | A. JAGOT | 1.0_P3  | Third proposed version with updates: Sequence diagrams

<br>
# 2.About this document

<br>
## 2.1.Purpose

This document contains a detailed description of the HAL implementation for DCACHE HAL module. The objectives of this document are:

- to create a module detailed design that fulfils the specified requirements in the DCACHE SW Requirements Specification document [1],
- to fulfill the requirements placed on the module by the hardware, if any,
- to fulfill the requirements placed on the module by other modules, if any,
- to fulfill the requirements placed on the module by the software architecture and design, if any,
- to design a module which is analyzable and verifiable, and which is capable of being safely modified.

The module detailed design describes the module interfaces (external and internal) in details, its structure as well as its control and data flows in such a way that code implementation can be achieved easily without having to take important technical decisions.

<br>
## 2.2.Scope

This document applies in the frame of the $FAMILYNAME_UC$ but also for all other projects including DCACHE IP. This document is intended for all software developers and testers assigned to the implementation or test of the DCACHE module.

<br>
## 2.3.Terms and acronyms definitions

Table 1: Terms definitions

Term   | Definition
------ | ----------
Safety | Freedom from unacceptable risk

Table 2: Acronyms definitions

Acronym | Definition
------- | ----------
DCACHE  | Data Cache
HAL     | Hardware Abstraction Layer
SDD     | Software Detailed Design

This document is written in compliance with Procedures identified in Table 3 below and relies on project information available in documents identified in Table 4.

Table 3: QMS Procedures

Title   | Version   | Doc ID/Link
------- | --------- | ----------
EmbSW module detailed design template | V2.0 | [cx564179](https://codex.cro.st.com/plugins/docman/index.php?group_id=3244&id=564179&action=show) 

Table 4: Project Documents

Title                                     | Version | Doc ID/Link
----------------------------------------- | ----------------- | -----------
[1] EmbSW_Cube2_IP_DCACHE_SRS             | V1.0              | [cx773252](https://codex.cro.st.com/plugins/docman/index.php?group_id=3244&id=773252&action=show)
[2] EmbSW_Cube2_Firmware_SAD              | V1.0              | [cx745929](https://codex.cro.st.com/plugins/docman/index.php?group_id=3244&id=745929&action=show)

<br>
# 3.Module general description

<br>
## 3.1.Introduction

insert section "Detailed Description" from \ref DCACHE

<br>
## 3.2.Principles

insert section "Modules/Detailed Description" from \ref DCACHE_Exported_Functions

<br>
## 3.3.Common Data
No private variables.

<br>
## 3.4.Dependencies

insert page from \subpage component_diagram

<br>
## 3.5.Functions, types, structures, and constants

<br>
### 3.5.1.Exported Functions Documentation

insert section "Modules/Function Documentation" from \ref DCACHE_Exported_Functions

<br>
### 3.5.2.Exported Typedef Documentation

insert section "Typedef Documentation" from \ref DCACHE_Exported_Types

#### DCACHE Handle Structure Definition

insert section "Data Structures/Field Documentation" from \ref DCACHE_Exported_Types

<br>
### 3.5.3.Exported Enumerations Type Documentation

insert section "Enumeration Type Documentation" from \ref DCACHE_Exported_Types

<br>
### 3.5.4.Exported Constants Definition Documentation

insert section "Modules/Macro Definition Documentation" from \ref DCACHE_Exported_Constants

<br>
### 3.5.5.Private Functions Documentation

insert section "Function Documentation" from \ref DCACHE_Private_Functions

<br>
### 3.5.6.Private Defines Definition Documentation

insert section "Macro Definition Documentation" from \ref DCACHE_Private_Defines

<br>
### 3.5.7.Private Macros Definition Documentation

insert section "Macro Definition Documentation" from \ref DCACHE_Private_Macros

<br>
# 4.Static overview

The call/caller graphs of DCACHE is available by parties thanks to the call/caller graph 
section in each function description at 3.5.1 Exported Functions Documentation
and / or 3.5.5 Private Functions Documentation.

<br>
# 5.Dynamic behavior

insert page from \subpage dynamic_behavior

<br>
# 6.Important Notice – Please read carefully

STMicroelectronics International NV and its affiliates (“ST”) reserve the right to make changes corrections, enhancements, modifications, and improvements to ST products and/or to this document any time without notice.
This document is provided solely for the purpose of obtaining general information relating to an ST product. Accordingly, you hereby agree to make use of this document solely for the purpose of obtaining general information relating to the ST product. You further acknowledge and agree that this document may not be used in or in connection with any legal or administrative proceeding in any court, arbitration, agency, commission or other tribunal or in connection with any action, cause of action, litigation, claim, allegation, demand or dispute of any kind. You further acknowledge and agree that this document shall not be construed as an admission, acknowledgement or evidence of any kind, including, without limitation, as to the liability, fault or responsibility whatsoever of ST or any of its affiliates, or as to the accuracy or validity of the information contained herein, or concerning any alleged product issue, failure, or defect. ST does not promise that this document is accurate or error free and specifically disclaims all warranties, express or implied, as to the accuracy of the information contained herein. Accordingly, you agree that in no event will ST or its affiliates be liable to you for any direct, indirect, consequential, exemplary, incidental, punitive, or other damages, including lost profits, arising from or relating to your reliance upon or use of this document.
Disclosure of this document to any non-authorized party must be previously authorized by ST only under the provision of a proper confidentiality contractual arrangement executed between ST and you and must be treat as strictly confidential.
At all times you will comply with the following securities rules:
 - Do not copy or reproduce all or part of this document.
 - Keep this document locked away.
 - Further copies can be provided on a “need to know basis”. Please contact your local ST Sales Office or document writer.

Purchasers should obtain the latest relevant information on ST products before placing orders. ST products are sold pursuant to ST’s terms and conditions of sale in place at the time of order acknowledgment, including, without limitation, the warranty provisions thereunder.
In that respect please note that ST products are not designed for use in some specific applications or environments described in above mentioned terms and conditions.
Purchasers are solely responsible for the choice, selection, and use of ST products and ST assumes no liability for application assistance or the design of purchasers’ products.
Information furnished is believed to be accurate and reliable. However, ST assumes no responsibility for the consequences of use of such information nor for any infringement of patents or other rights of third parties which may result from its use. No license, express or implied, to any intellectual property right is granted by ST herein.
Resale of ST products with provisions different from the information set forth herein shall void any warranty granted by ST for such product.
ST and the ST logo are trademarks of ST. For additional information about ST trademarks, please refer to www.st.com/trademarks. All other product or service names are the property of their respective owners.
Information in this document supersedes and replaces information previously supplied in any prior versions of this document.
© 2022 STMicroelectronics – All rights reserved