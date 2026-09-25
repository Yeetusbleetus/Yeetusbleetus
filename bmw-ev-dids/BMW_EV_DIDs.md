# BMW EV / hybrid UDS DID catalogue

Generated from EDIABAS SGBD `SG_FUNKTIONEN` tables. See `tools/` for the parser.

| Vehicle | Generation | ECU | Role | Diag addr | Functions | Read | Write | Routine | Sources |
|---|---|---|---|---|---:|---:|---:|---:|---|
| BMW i3 / i3s (I01) | Gen3 BEV (2013-2022) | SME | HV battery management | 0x07 | 215 | 134 | 65 | 25 | sme_i1.prg (OVMS dump, GPL-3.0)<br>sme_i1.prg rev 0.911 (2012) |
| BMW i3 / i3s (I01) | Gen3 BEV (2013-2022) | EME | Drive inverter + DC/DC | 0x1A | 137 | 94 | 42 | 22 | eme_i01.prg (OVMS dump, GPL-3.0)<br>eme_i01.prg rev 0.540 (2012) |
| BMW i3 / i3s (I01) | Gen3 BEV (2013-2022) | EME | Drive electronics (alternate SGBD EME_I1) | 0x1A | 55 | 35 | 16 | 7 | EME_I1.prg rev 1.1 (2012) |
| BMW i3 / i3s (I01) | Gen3 BEV (2013-2022) | KLE | On-board charger (UCX2) | 0x15 | 18 | 16 | 0 | 2 | ucx2_i01.prg (OVMS dump, GPL-3.0) |
| BMW i3 / i3s (I01) | Gen3 BEV (2013-2022) | LIM | Charge interface module | 0x14 | 21 | 18 | 12 | 0 | lim_i1.prg (OVMS dump, GPL-3.0)<br>lim_i1.prg rev 2.0 (2012) |
| BMW i3 / i3s (I01) | Gen3 BEV (2013-2022) | IHX | Heating/AC, heat pump, HV heater | 0x78 | 156 | 131 | 44 | 4 | ihx_i1.prg (OVMS dump, GPL-3.0)<br>ihx_i1.prg rev 1.7 (2012) |
| BMW i3 / i3s (I01) | Gen3 BEV (2013-2022) | EDME | Vehicle control unit / 12V energy mgmt | 0x12 | 70 | 35 | 7 | 15 | edmei1.prg (OVMS dump, GPL-3.0)<br>edmei1.prg rev 2.345 (2012) |
| BMW i3 REx (I01) | Gen3 BEV (2013-2022) | REME | Range-extender generator electronics |  | 11 | 9 | 0 | 2 | reme_i1.prg rev 0.401 (2012) |
| BMW i3 REx (I01) | Gen3 BEV (2013-2022) | RDME | Range-extender engine DME |  | 83 | 73 | 0 | 6 | rdme_i1.prg rev 0.220 (2012) |
| BMW i8 (I12) | Gen3 PHEV (2014-2020) | EME | Front e-machine electronics |  | 80 | 51 | 20 | 12 | eme_i12.prg rev 0.417 (2012) |
| BMW i8 (I12) | Gen3 PHEV (2014-2020) | REME | High-voltage starter-generator electronics |  | 11 | 9 | 0 | 2 | reme_i12.prg rev 0.200 (2012) |
| BMW 530Le (F18) | Gen2 PHEV (2014-2017, China) | SME | HV battery management |  | 40 | 28 | 9 | 5 | sme_f18.prg rev 0.107 (2012) |
| BMW 530Le (F18) | Gen2 PHEV (2014-2017, China) | EME | E-machine electronics |  | 67 | 42 | 15 | 12 | eme_f18.prg rev 0.819 (2012) |
| BMW X5 xDrive40e (F15) | Gen2 PHEV (2015-2018) | SLE | Charging electronics incl. LIM |  | 31 | 29 | 4 | 2 | sle_f15.prg rev 0.2 (2012) |
| ActiveHybrid 3/5/7 (F30/F10/F01) | Hybrid Gen 2.0 (2012-2016) | SME | HV battery management |  | 94 | 72 | 26 | 2 | sme_10.prg rev 3.4 (2011) |
| ActiveHybrid 3/5/7 (F30/F10/F01) | Hybrid Gen 2.0 (2012-2016) | EME | E-machine electronics |  | 73 | 54 | 14 | 8 | eme_10.prg rev 16.0 (2012) |
| ActiveHybrid 7 (F04) | Hybrid Gen 1.5 (2009-2012) | SME | HV battery management |  | 36 | 28 | 6 | 3 | SME_04_029.prg rev 0.29 (2008)<br>sme_04.prg rev 2.3 (2009) |
| ActiveHybrid 7 (F04) | Hybrid Gen 1.5 (2009-2012) | EME | E-machine electronics |  | 247 | 229 | 9 | 10 | EME_04_490.prg rev 4.200 (2009)<br>EME_04_I410.prg rev 1.1 (2009)<br>EME_04_nur_I300.prg rev 0.14 (2008)<br>eme_04.prg rev 8.12 (2010)<br>eme_04_I260.prg rev 0.12 (2008)<br>eme_04_alt.prg rev 1.1 (2009) |
| BMW ActiveE (E82, "BEV10") | Gen1 BEV (2011-2013) | SME | HV battery management (master) |  | 79 | 60 | 23 | 1 | SME_82.prg rev 1.1 (2011) |
| BMW ActiveE (E82, "BEV10") | Gen1 BEV (2011-2013) | SMES1 | HV battery management slave 1 |  | 89 | 68 | 25 | 1 | SMES1_82.prg rev 1.0 (2011) |
| BMW ActiveE (E82, "BEV10") | Gen1 BEV (2011-2013) | SMES2 | HV battery management slave 2 |  | 89 | 68 | 25 | 1 | SMES2_82.prg rev 1.0 (2011) |
| BMW ActiveE (E82, "BEV10") | Gen1 BEV (2011-2013) | KLE | On-board charger |  | 32 | 32 | 3 | 0 | KLE_82E.prg rev 2.0 (2012) |

## BMW i3 / i3s (I01) — SME (HV battery management)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x6334` | 22 | `ALTERUNG_INNENWIDERSTAND_TS` | Aging of the internal resistance in percent: Internal resistance of the storage tank when new is related to the current value of the internal resistance (R_neu / R_akt) * 100 (100% = new condition, decreases with aging) | 1 |
| `0x6335` | 22 | `ALTERUNG_KAPAZITAET_TS` | Remaining capacity of the memory | 1 |
| `0x6500` | 2E | `_SOC_GRENZEN` | State of charge limit values | 2 |
| `0x6501` | 2E | `_ISOLATION` | Insulation monitoring | 2 |
| `0x6502` | 2E | `_UEBERLAST_SCHWELLE` | Charge and discharge current limits | 2 |
| `0x6503` | 2E | `_KURZSCHLUSS_STROMGRENZE` | Short circuit current limit | 2 |
| `0x6504` | 2E | `_LADE_SPANNUNGSGRENZE` | Load voltage limit | 2 |
| `0x6506` | 2E | `_SCHUETZ_K1` | K1 contactor | 2 |
| `0x6507` | 2E | `_SCHUETZ_K2` | K2 contactor | 2 |
| `0x6508` | 2E | `_SCHUETZ_K3` | K3 contactor | 2 |
| `0x650B` | 2E | `_ENTLADE_SPANNUNGSGRENZE` | Discharge voltage limit | 2 |
| `0x6511` | 2E | `_SYM_MODUS` | Symmetry mode of the SEM | 2 |
| `0x6512` | 2E | `_MESSBOTSCHAFTEN` | Switch measurement messages on / off | 2 |
| `0x6516` | 22 | `_ST_SYM_MODUS` | Status of the balancing | 1 |
| `0x6519` | 2E | `_CSC_STANDBY` | Put CSCs in standby mode | 2 |
| `0x651B` | 2E | `_ANFORDERUNG_SCHUETZE_SCHLIESSEN` | Close contactor | 2 |
| `0x651C` | 2E | `_STEUERN_PRUEFSTANDSMODUS` | Open the operating limits of SOC, current, voltage and temperature up to the safety limits and deactivate the ISO monitor | 2 |
| `0x651D` | 22 | `_UEBERLAST_ZAHELER` | Diagnostic job to read out the overload failures that have occurred for warranty returns | 8 |
| `0x651F` | 2E | `_NV_DATA_RESET` | Reset NV data of the SME to the initial state | 2 |
| `0x6525` | 2E | `_STEUERN_UEBERNAHME_KAPATEST_NV` | Diagnostic switch to control the transfer of the result of a capacity test to the SoH_C estimator | 2 |
| `0x6526` | 22 | `_STATUS_UEBERNAHME_KAPATEST_NV` | Current setting of the transfer of the results of a capacity test to the SoH_C estimator (0: no transfer, 1: transfer (standard)) | 1 |
| `0x6527` | 2E | `_ADRESSBEREICH` | '' This control job can be used to activate a switchover of the SME to one of 16 predefined CAN address areas in conjunction with one of 16 predefined diagnostic addresses that deviate from the standard SME addresses. | 2 |
| `0x6528` | 2E | `_DEM_TEST` | Activate fault memory test | 2 |
| `0x6529` | 2E | `_DEM_TEST_EINTRAG` | Set fault memory entry in test mode | 2 |
| `0xAD5E` | 31 | `ISOLATIONSWIDERSTAND_KOMMUNIKATION` | JOB CANCELED Activation of the BN signal AVL_ISRE on the vehicle bus. | 1 |
| `0xAD61` | 31 | `ISOLATION` | Isolation test result | 2 |
| `0xAD66` | 31 | `KAPAZITAET_BESTIMMUNG` | Determination of the capacity | 2 |
| `0xAD6A` | 31 | `HEIZUNG` | Activation and reading of the heating in the HV battery | 1 |
| `0xAD6B` | 31 | `SYMMETRIERUNG` | Activate balancing | 1 |
| `0xAD6C` | 31 | `ZELLSPANNUNG_UNPLAUSIBEL_LESEN` | Returns the module number of the CSCs in which an implausible voltage value was detected (linked to DTC). The return value is a component vector length 8) with the assignment 0 = no error, 1 = error detected. | 2 |
| `0xAD6D` | 31 | `MODULTEMPERATUREN_LESEN` | Currently measured temperature from the selected module | 2 |
| `0xAD6E` | 31 | `ZELLSPANNUNG_LESEN` | Cell whose voltage is to be determined | 2 |
| `0xAD6F` | 31 | `HIS_TEMP_MOD_LESEN` | Time (minutes with HVON and 100ms with NO_OP) in various temperature classes of the maximum and minimum cell temperature of individual modules (storage in operation) and the mean cell temperature of the individual modules (storage out of operation). ATTENTION: The correct unit of the output value STAT_HIS_TEMP_NO_OP_MOD_MEAN_X_WERT is [100ms] and not [min] as entered in the UNIT box. The counter can start again from zero around 13.2 years from the beginning of the logging process due to integer overflow. | 27 |
| `0xAD70` | 31 | `HIS_ERR_LIM_SPANNUNG_MOD_LESEN` | Output of the dwell time in voltage fault limit classes of individual modules. At temperatures <-10 ° C, the voltage error limit changes depending on the temperature. (Samsung) | 7 |
| `0xAD71` | 31 | `HIS_SPANNUNG_MOD_LESEN` | Time in minutes in different voltage classes of individual modules | 7 |
| `0xAD73` | 31 | `HEIZUNG_FUNKTION` | Execution of the functional diagnosis heating | 1 |
| `0xAD74` | 31 | `HIS_ZELL_DSOCS_LESEN` | Reading out the totaled Delta_SOC values of all individual cells over X_end driving cycles (X_end = 30, can be calibrated). | 3 |
| `0xAD75` | 31 | `SYMMETRIERUNG_FIXSPG` | Triggering the voltage-controlled balancing by means of the target voltage specification | 2 |
| `0xAD76` | 31 | `CSC_IDS_LESEN` | Enter the CSC number to read out the DMC from CSC x | 2 |
| `0xAD77` | 31 | `STEUERN_MIN_KAPAZITAET_MOD_LESEN` | Reading out the current minimum capacity of module x, based on the capacity quotient (capacity quotient = (C_akt / C_nenn (new)) * 100 (100% = corresponds to nominal capacity; capacity quotient> 100% corresponds to cell capacity> nominal capacity, capacity quotient <100% corresponds to cell capacity <nominal capacity) . | 2 |
| `0xAD78` | 31 | `MAX_INNENWIDERSTANDSFAKTOR_MOD_LESEN` | Reading out the current maximum internal resistance factor of module x, (factor = 0-5 with two decimal places; factor &lt;1 corresponds to a reduced cell internal resistance compared to the average, factor&gt; 1 corresponds to an increased cell resistance compared to the average) | 2 |
| `0xAD79` | 31 | `ZELLPACK_STATUS_LESEN` | Reading out the aging status (e.g. defect, etc.) of module x | 2 |
| `0xAD7A` | 31 | `SBOX_ANZAHL_TAUSCH_LESEN` | Incrementing and reading of the SBOX replacement counter. The counter will be incremented every time the SBOX is replaced by a diagnostic job. | 2 |
| `0xAD7C` | 31 | `HIS_SPANNUNG_NOP_MOD_LESEN` | Time in 100ms in different voltage classes of individual modules while the memory is not in operation ATTENTION: The correct unit of the output value STAT_HIS_SPANNUNG_NOP_MOD_X_WERT is [100ms] and not [min] as entered in the UNIT box. The counter can start again from zero around 13.2 years from the beginning of the logging process due to integer overflow. | 7 |
| `0xAD7D` | 31 | `ZELLPACK_DMC_LESEN` | This job reads out the DMC from cell pack x. | 2 |
| `0xD4C5` | 22 | `RB_SOC_REKALIBRIERUNG` | Reading out the battery status BEFORE and AFTER the last 5 SOC recalibrations | 125 |
| `0xD4C6` | 22 | `RB_SOH_ADAPTION` | This job is no longer requested and is no longer supported (all returns deliver '0') | 120 |
| `0xD4C7` | 22 | `SOC_GUETE` | Reading out the current SOC quality value based on the SOC estimate (1 == best quality,> 30 == worst quality) | 1 |
| `0xD4C8` | 22 | `HIS_SOC_GUETE` | Reading out the length of stay in 5 classes of the SOC quality value based on the SOC estimate | 5 |
| `0xD4C9` | 22 | `ANZAHL_OCV_SOC_REKAL` | Number of OCV-SOC recalibrations | 1 |
| `0xD4CA` | 22 | `ANZAHL_LADEENDE_REKAL` | Number of SoC recalibrations at the end of charging | 1 |
| `0xD4CB` | 22 | `RB_SOC_VOLLADEENDE` | Reading out different SOCs of the last 5 full charges | 30 |
| `0xD4CC` | 22 | `KUEHLDAUER_HVB` | Job is not relevant for SME_03 // Replacement is STATUS_KUEHLDAUER Cooling time of the HV battery | 5 |
| `0xD67F` | 22 | `LADUNGSVERLUST_ZELLE` | Ring memory for the loss of charge in the cells | 12 |
| `0xD681` | 22 | `STATUS_MIN_KAPAZITAET_MOD` | Reading of the current minimum capacity of ALL modules, based on the capacity quotient. | 12 |
| `0xD6C7` | 22 | `RB_ISO_MESS_TRG` | Return of the R_iso including quality of the last 5 follow-up measurements | 10 |
| `0xD6C8` | 22 | `RB_ISO_MESS_STD_IO_NIO` | Return of the last 10 events of the R_iso standard measurement when the error threshold is undershot / exceeded | 30 |
| `0xD6C9` | 22 | `RB_ISO_MESS_TRG_IO_NIO` | Return of the last 10 events of the triggered follow-up ISO measurement when the error threshold is undershot / exceeded | 30 |
| `0xD6CA` | 22 | `ISODIAG_INPUT_ISTWERTE` | Return of input signals of the R_ISO calculation formula | 10 |
| `0xD6CB` | 22 | `ISO_ERR_STD_FZ1_2` | Return of input signals and result values of the standard ISO measurement at error time 1 and 2 | 33 |
| `0xD6CC` | 22 | `RB_SOH_KAPATEST` | Return of the results of the last 3 HVS offboard capacity tests (ring memory) | 24 |
| `0xD6CD` | 22 | `REKU_VOLTAGE_LIFT` | Return of the duration and frequency in which the increased recuperation is made available when the HVS is almost full | 2 |
| `0xD6CE` | 22 | `RB_ALTERUNG_KAPA` | Return of the results of the last 5 SoH_C adaptations including capacity tests (ring memory) | 113 |
| `0xD6CF` | 22 | `CSC_TEMPERATUREN` | Return of the current temperature measured values of all CSC sensors (max 3 * 12, without HW-RL) | 24 |
| `0xD6D1` | 22 | `ISO_ERR_TRG_FZ1_2` | Return of input signals and result values of the triggered follow-up ISO measurement at error time 1 and 2 | 33 |
| `0xDD60` | 22 | `SCHUETZ_SCHALTER` | Contactor switch status: closed, open, welded contacts or not defined. For results see table TAB_SCHUETZ_SCHALTER | 1 |
| `0xDD61` | 2E;22 | `SCHUETZ_FREIGABE` | Writes or reads the bit to enable or disable the contactor switch. Job is clamp-safe | 2 |
| `0xDD63` | 22 | `SCHUETZSCHALTUNGEN_ANZAHL` | Number of switchings of the contactor switch (currentless and under load) | 2 |
| `0xDD64` | 22 | `HVIL` | HVIL test result | 1 |
| `0xDD66` | 22 | `HV_SPANNUNG` | Intermediate circuit voltage to the HV connection plug, depending on the contactor status | 1 |
| `0xDD67` | 22 | `ANZAHL_KUEHLANFORDERUNG_DRINGEND` | Number of consecutive wake cycles with urgent cooling requirements (service life max. Value) | 1 |
| `0xDD68` | 22 | `HV_SPANNUNG_BERECHNET` | Battery voltage behind the contactors, regardless of the contactor status | 1 |
| `0xDD69` | 22 | `HV_STROM` | HV current in A | 1 |
| `0xDD6A` | 22 | `ISOLATIONSWIDERSTAND` | Reading out the currently applied insulation resistance | 6 |
| `0xDD6C` | 22 | `KUEHLKREISLAUF_TEMP` | Temperature of the cooling medium in ° C (327.67 = implausible) | 1 |
| `0xDD6E` | 2E | `SCHUETZE_MAX_SOC_SICHERHEITABFRAGE` | NO JOB Main contactors switch when the SOC is greater than 90%. Caution: This job must be secured with a security query in all subsequent tools. - This job is NO longer supported! | 2 |
| `0xDD6F` | 2E;22 | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: Closed or open / close or open | 2 |
| `0xDD72` | 22 | `AUFSTART_VERHINDERER` | Reason for not starting the HV system | 1 |
| `0xDD73` | 22 | `CUMULATIVE_LADUNG` | The accumulated charge for charges in Ah | 1 |
| `0xDD74` | 22 | `CUMULATIVE_ENTLADUNG` | The accumulated charge for discharges in Ah | 1 |
| `0xDD76` | 22 | `STATUS_KL30C_SPANNUNG` | Voltage terminal 30C in V | 1 |
| `0xDD78` | 2E | `SOC_REKALIBRIERUNG` | Recalibration of the SoC estimator in order to obtain the current SoC after a long storage period. ## Job may only be carried out with OPEN shooters! ATTENTION with SE07: With BEV vehicles, the job also resets a recognized end of the journey (completely discharged / defective cell)! | 1 |
| `0xDD79` | 2E | `SCHUETZE_MIN_SOC_SICHERHEITABFRAGE` | JOB CANNOTED Main contactors switch at min SOC (less than 5% SOC). Caution: This job must be secured with a security query in all subsequent tools. Cannot be executed while driving. - This job is NO longer supported! | 2 |
| `0xDD7B` | 22 | `ALTERUNG_KAPAZITAET` | Readout of the battery capacity adjustment | 1 |
| `0xDD7C` | 22 | `GW_INFO` | Warranty data | 27 |
| `0xDD7D` | 22 | `STROMGRENZEN` | Current limits | 2 |
| `0xDD7E` | 22 | `SPANNUNGSGRENZEN` | Voltage limits | 2 |
| `0xDD8E` | 22 | `HVB_HISTORIE_ZYKLEN` | Output of the current load (current histogram) | 30 |
| `0xDD90` | 22 | `ZEIT_TEMP_HISTOGRAMM` | Time in different temperature classes and control unit states (SG awake, SG asleep) of the averaged calculated temperature over all cell nuclei | 28 |
| `0xDD91` | 22 | `ZEIT_SOC_KLASSE` | Returns the length of stay of the SoC in SoC classes over the service life - SE03 from 11/13 total duration (sleep + awake) - up to 11/13 only operating time (awake) | 12 |
| `0xDD94` | 22 | `HV_BATT_HIST_SOC_T1_1` | Duration at temperature less than 0 ° C and with different values of current and SOC - part 1 | 40 |
| `0xDD95` | 22 | `HV_BATT_HIST_SOC_T2_1` | Duration at 0 ° C less than temperature less than 10 ° C and with different values of current and SOC - part 1 | 40 |
| `0xDD96` | 22 | `HV_BATT_HIST_SOC_T3_1` | Duration at 10 ° C less than temperature less than 20 ° C and with different values of current and SOC - part 1 | 40 |
| `0xDD97` | 22 | `HV_BATT_HIST_SOC_T4_1` | Duration at 20 ° C less than temperature less than 27.5 ° C and with different values of current and SOC - part 1 | 40 |
| `0xDD98` | 22 | `HV_BATT_HIST_SOC_T5_1` | Duration at 27.5 ° C less than temperature less than 32.5 ° C and with different values of current and SOC - part 1 | 40 |
| `0xDD99` | 22 | `HV_BATT_HIST_SOC_T6_1` | Duration at 32.5 ° C less than temperature less than 40 ° C and with different values of current and SOC - part 1 | 40 |
| `0xDD9A` | 22 | `HV_BATT_HIST_SOC_T7_1` | Duration at 40 ° C less than temperature and with different values of current and SOC - part 1 | 40 |
| `0xDDAB` | 22 | `LADEZIELSPANNUNG_TAUSCH` | Output of the charging target voltage for module replacement before installing the module in the vehicle | 1 |
| `0xDDB4` | 22 | `HV_SPANNUNG_BATTERIE` | Battery voltage behind the contactors, regardless of the contactor status | 1 |
| `0xDDB6` | 22 | `ALTERUNG_INNENWIDERSTAND` | Aging of the internal resistance in percent: Internal resistance of the storage tank when new is related to the current value of the internal resistance (R_neu / R_akt) * 100 (100% = new condition, decreases with aging) | 1 |
| `0xDDB7` | 2E;22 | `REFERENZ_KAPAZITAET` | Remaining capacity of the memory, percentage value: (C_akt / C_nenn (new)) * 100, 100 = new state. Raw estimate of the onboard capacity estimate of total storage | 2 |
| `0xDDBC` | 22 | `ANZEIGE_SOC` | current advertisement Soc | 3 |
| `0xDDBD` | 22 | `SERVICE_DISCONNECT` | Status Service Disconnect (0 = open, 1 = closed) | 1 |
| `0xDDBE` | 22 | `VORLADUNG` | Info about time, current and temperatures during pre-charging | 10 |
| `0xDDBF` | 22 | `ZELLSPANNUNGEN_MIN_MAX` | minimum and maximum single cell voltages are output | 2 |
| `0xDDC0` | 22 | `TEMPERATUREN` | Output of the calculated cell core temperatures (minimum, maximum and average) | 3 |
| `0xDDC2` | 22 | `ALTERUNG_PARAMETER` | Correction factor of the serial and parallel ohmic resistance as well as the parallel capacitance (1.5 = increase in resistance by 50%) | 3 |
| `0xDDC4` | 2E;22 | `SOC` | Read out SOC value (in%) and plausibility or specification of the SOC value (0-100%) | 4 |
| `0xDDC6` | 22 | `HISTO_SYM_DAUER` | Reading out the number of balancing processes in the respective time classes (actual time in which the balancing resistors were active) | 9 |
| `0xDDC7` | 22 | `HISTO_SYM_ZELLANZAHL` | Frequency over the lifetime of the number of cells that were instructed for balancing. Increment if symmetry is required when falling asleep after FIRST cyclical waking up. | 8 |
| `0xDDC8` | 22 | `SYM_DELTASOC` | Maximum SoC difference in% over the entire HVS. Ring memory of the last 5 trips | 5 |
| `0xDDC9` | 22 | `MAX_SYM_DAUER` | Maximum symmetry duration of the last symmetrization process | 15 |
| `0xDDCA` | 22 | `SERIENNUMMER_ECU` | Serial number of the SME control unit | 1 |
| `0xDDCB` | 22 | `SOC_GRENZEN` | Reading and changing the SOC limits | 2 |
| `0xDDCC` | 2E;22 | `SCHUETZ_RESTZAEHLER` | Read out or reset (0 = no reset; 1 = reset) of the counter for the possible switching of contactors K1, K2, K3 | 4 |
| `0xDDCD` | 2E | `CC_MELDUNG` | Activation / deactivation of the sending of CC messages (0 = sending not active; 1 = sending active) | 1 |
| `0xDDCF` | 22 | `DIFFERENZ_SPANNUNGEN` | Differential voltage: total voltage HV battery - total cell voltage (static determination) | 1 |
| `0xDDE8` | 22 | `ALTERUNG_KAPAZITAET_DEGRADATION` | Number of age-related stress degradations | 2 |
| `0xDDE9` | 22 | `ALTERUNG_KAPAZITAET_HISTOGRAMM_SOC_HUB` | Histogram with the frequency of individual SoC strokes that occurred during the operating period | 24 |
| `0xDDEA` | 2E | `RESET_SBOX_ANZAHL_TAUSCH` | Resetting the SBOX exchange counter | 2 |
| `0xDDEB` | 22 | `RINGPUFFER_LADEVORGAENGE` | Return of measured variables of the last 5 completed charging processes: - Start SOC - Available charging power - Actual end SOC - Reason charging end (no charging end detected 0, target SOC reached 1, U / I full charge detection 2, external cancellation 3, error SME 4 ) - Start temperature - End temperature - Charging time forecast at the beginning in min - Actual charging time in min - Relative time (continuous combination system time from ACAN with start in the factory) | 45 |
| `0xDDEC` | 22 | `HIS_PROG_LADEZEIT` | Representation of the frequency of a relative deviation of the charging time forecast from the real value (fact = (t_prog-t_ist) / t_ist * 100%). t_prog = predicted value at the beginning of the charging phase. t_ist = time actually required to reach the loading target. | 7 |
| `0xDDED` | 2E | `CSC_IDS_ZUORDNEN` | Assign indices / installation position of the individual CSCs | 2 |
| `0xDDEE` | 2E | `CSC_IDS_UEBERNEHMEN` | Take over indices / installation position of the individual CSCs in SME | 1 |
| `0xDDEF` | 22 | `HV_SPANNUNG_QUER` | SBox, high-voltage transverse (same as battery voltage when K1 or K3 is closed) | 1 |
| `0xDE37` | 22 | `ALPHA_INITIAL_ALTERUNG` | Initial value of the SOH_R calculation | 1 |
| `0xDF60` | 22 | `BETRIEBSSTUNDEN` | Time for closed main switch and total battery life (closed and open time of main switch) | 2 |
| `0xDF62` | 22 | `COOL_DOWN` | Number of CoolDown scenarios (departure with hot HV storage) | 1 |
| `0xDF63` | 22 | `KLEMMENZYKLEN` | Number of terminal cycles | 1 |
| `0xDF64` | 22 | `KUEHLDAUER` | HV battery cooling time | 5 |
| `0xDF65` | 22 | `TEMP_SPREIZUNG_SYSTEM` | Time in different dT classes with active cooling | 7 |
| `0xDF66` | 22 | `TEMP_KUEHLMITTEL` | Time in different temperature classes of the coolant | 7 |
| `0xDF67` | 22 | `LADUNG_KUEHLUNG` | Amount of charge and discharge with the cooling switched on | 2 |
| `0xDF68` | 22 | `HV_BATT_HIST_SOC_T1_2` | Duration at temperature less than 0 ° C and with different values of current and SOC - part 2 | 30 |
| `0xDF69` | 22 | `HV_BATT_HIST_SOC_T4_2` | Duration at 20 ° C less than temperature less than 27.5 ° C and with different values of current and SOC - part 2 | 30 |
| `0xDF6A` | 22 | `HV_BATT_HIST_SOC_T3_2` | Duration at 10 ° C less than temperature less than 20 ° C and with different values of current and SOC - Part 2 | 30 |
| `0xDF6B` | 22 | `HV_BATT_HIST_SOC_T5_2` | Duration at 27.5 ° C less than temperature less than 32.5 ° C and with different values of current and SOC - part 2 | 30 |
| `0xDF6C` | 22 | `HV_BATT_HIST_SOC_T2_2` | Duration at 0 ° C less than temperature less than 10 ° C and with different values of current and SOC - part 2 | 30 |
| `0xDF6D` | 22 | `HV_BATT_HIST_SOC_T7_2` | Duration at 40 ° C less than temperature and with different values of current and SOC - part 2 | 30 |
| `0xDF6E` | 22 | `HV_BATT_HIST_SOC_T6_2` | Duration at 32.5 ° C less than temperature less than 40 ° C and with different values of current and SOC - part 2 | 30 |
| `0xDF6F` | 22 | `HIS_ERR_LIM_STROM` | Time in minutes in different current error limit classes separately for charging and discharging over all temperatures | 6 |
| `0xDF70` | 22 | `HIS_EFF_STROM` | Time in minutes in different effective current value classes separately for charging and discharging | 12 |
| `0xDF71` | 22 | `PROJEKT_PARAMETER` | Reading out the project-specific parameters | 4 |
| `0xDF72` | 22 | `KURZSCHLUESSE` | Number of short circuits that occurred | 1 |
| `0xDF73` | 22 | `HEIZUNG_VERBAUT` | Status heating installed (0 = no / 1 = yes) | 1 |
| `0xDF74` | 22 | `VOKO_HEIZ_DAUER` | Number of preconditioning heating cycles | 7 |
| `0xDF75` | 22 | `LADE_KOND_HEIZ_DAUER` | Number of heating conditioning processes during charging | 7 |
| `0xDF76` | 22 | `VOKO_KUEHL_DAUER` | Number of pre-conditioning cooling cycles | 7 |
| `0xDF77` | 22 | `LADE_DAUER` | Number of charging processes in charging duration classes | 7 |
| `0xDF78` | 2E | `RESET_HIS_TEMP_MOD` | Reset the temperature histogram of the selected module | 1 |
| `0xDF79` | 2E | `RESET_HIS_ERR_LIM_SPANNUNG_MOD` | Reset the voltage error limit histogram of the selected module | 1 |
| `0xDF7A` | 2E | `RESET_HIS_SPANNUNG_MOD` | Reset the voltage histogram of the selected module | 1 |
| `0xDF7B` | 2E | `RESET_ISOLATIONSMESSWERTE` | Resetting the insulation resistance readings | 2 |
| `0xDF7C` | 2E | `ENTLADESPANNUNGSGRENZE_UNTEN` | Set the discharge voltage limit down to enable connection in the event of cell undervoltage | 2 |
| `0xDF7D` | 2E | `RESET_ZELLKAPAZITAETEN` | Resetting the stored single cell capacities | 1 |
| `0xDF7E` | 2E | `RESET_ZELL_DSOCS` | Job has not been requested for SME_03 since I001_14-03-490 and has been replaced by STEUERN_SOC_REKALIBRIERUNG Resetting the stored Delta SOCs | 1 |
| `0xDF7F` | 2E | `ZELLKAPAZITAETEN` | Setting the capacity of module x or all modules to a certain value | 2 |
| `0xDF80` | 2E | `SERIENNUMMER_SCHREIBEN` | Writing the HV storage serial number | 2 |
| `0xDF81` | 22 | `HIS_SOC_WARN_GRENZEN` | Operating time in minutes in the lower and upper SOC warning limits | 9 |
| `0xDF83` | 22 | `ID_SBOX` | Reading out the identification parameters of the SBOX | 5 |
| `0xDF84` | 2E | `PUFFER_ZELLSPANNUNGEN` | Holding the cell voltage for a time step | 1 |
| `0xDF86` | 22 | `SOC_HISTORIE` | Reading out the SOC history data | 13 |
| `0xDF87` | 2E | `ZELLPACK_IDS_ZUORDNEN` | Assign indices / installation position of the individual cell packs | 2 |
| `0xDF88` | 2E | `ZELLPACK_IDS_UEBERNEHMEN` | Transfer indices / installation position of the individual cell packs in SME | 1 |
| `0xDF89` | 22 | `KL30C` | Reading out the logical status of the KL30C> not for I01 and I12, use STATUS_KL30C_SPANNUNG here | 1 |
| `0xDF8A` | 22 | `HIS_EFF_STROM_TMIN` | At T <-10: time in minutes in different percentage value classes for the ratio of effective current to current limit separately for charging and discharging (SBL) | 12 |
| `0xDF8B` | 22 | `HIS_EFF_STROM_TLOW` | At -10 <= T <5: time in minutes in various percentage value classes for the ratio of effective current to current limit separately for charging and discharging (SBL) | 12 |
| `0xDF8C` | 22 | `HIS_EFF_STROM_TMID` | At 5 <= T <25 (40 SP01): Time in minutes in various percentage value classes for the ratio of effective current to current limit separately for charging and discharging (SBL) | 12 |
| `0xDF8D` | 22 | `HIS_EFF_STROM_THIGH` | ONLY SE03 !!! At 25 <= T <40: Time in minutes in different percentage classes for the ratio of effective current to current limit separately for charging and discharging (SBL) | 12 |
| `0xDF8E` | 22 | `HIS_EFF_STROM_TMAX` | At 40 <= T: time in minutes in various percentage value classes for the ratio of effective current to current limit separately for charging and discharging (SBL) | 12 |
| `0xDF8F` | 22 | `HIS_ERR_LIM_STROM_TMIN` | At T <= -10: time in minutes in different current error limit classes separately for charging and discharging | 6 |
| `0xDF90` | 22 | `HIS_ERR_LIM_STROM_TLOW` | At -10 <T <= 5: time in minutes in different current error limit classes separately for charging and discharging | 6 |
| `0xDF91` | 22 | `HIS_ERR_LIM_STROM_THIGH` | If 5 <T <= 25: time in minutes in different current error limit classes separately for charging and discharging | 6 |
| `0xDF92` | 22 | `HIS_ERR_LIM_STROM_TMAX` | At 25 <T: time in minutes in different current error limit classes separately for charging and discharging | 6 |
| `0xDF93` | 2E | `RESET_ALTERUNG_INNENWIDERSTAND` | Reset job is no longer relevant. Internal resistance is automatically adjusted when the module is replaced. | 1 |
| `0xDF94` | 2E | `RESET_ALTERUNG_KAPAZITAET_HIST_SOC_HUB` | Resetting the histogram that is read out with the job: STATUS_ALTERUNG_KAPAZITAET_HISTOGRAMM_SOC_HUB >> to be carried out when replacing modules | 1 |
| `0xDF95` | 2E | `RESET_BETRIEBSSTUNDEN_HVS` | Resetting the histogram that is read out with the job: STATUS_BETRIEBSSTUNDEN_SME (I01) STATUS_BETRIEBSSTUNDEN_HVS (future projects) >> Attention: for all SME functions, the entire HVS appears as absolutely NEW with this reset. Resetting is therefore only recommended when replacing many or all modules! | 1 |
| `0xDF96` | 2E | `RESET_ANZAHL_KUEHLANFORDERUNG_DRINGEND` | Resetting the histogram that is read out with the job: STATUS_ANZAHL_KUEHLANFORDERUNG_DRINGEND >> to be carried out when replacing modules | 1 |
| `0xDF97` | 2E | `RESET_CUMULATIVE_ENT_LADUNG` | Resetting the histogram that is read out with the job: STATUS_CUMULATIVE_ENTLADUNG STATUS_CUMULATIVE_LADUNG >> to be carried out when replacing modules | 1 |
| `0xDF98` | 2E | `RESET_HIS_EFF_ERR_LIM_STROM_ALL` | Resetting the histogram that is read out with the job: STATUS_HIS_EFF_STROM_Txxxx STATUS_HIS_ERR_LIM_STROM_Txxxx >> to be carried out when replacing modules | 1 |
| `0xDF99` | 2E | `RESET_HIS_SOC_WARN_GRENZEN` | Resetting the histogram that is read out with the job: STATUS_HIS_SOC_WARN_GRENZEN >> to be carried out when replacing modules | 1 |
| `0xDF9A` | 2E | `RESET_ZEIT_SOC_KLASSE` | Resetting the histogram that is read out with the job: STATUS_ZEIT_SOC_KLASSE >> to be carried out when replacing a module | 1 |
| `0xDF9B` | 2E | `RESET_ZEIT_TEMP_HISTOGRAMM` | Resetting the histogram that is read out with the job: STATUS_ZEIT_TEMP_HISTOGRAMM >> to be carried out when replacing modules | 1 |
| `0xDF9C` | 22 | `LADEZEIT_ADAPT_KENNFELD_LESEN` | Reading out the map of learning factors to correct the charging time prognosis raw value | 51 |
| `0xDF9D` | 2E | `RESET_LADEZEIT_ADAPT_KENNFELD` | Resetting to the initial value of the map of learning factors to correct the charging time forecast raw value. >> to be carried out when replacing a module Info: Readout of the reset initial values possible by subsequently carrying out LADEZEIT_ADAPT_KENNFELD_LESEN. | 1 |
| `0xDF9E` | 22 | `VERH_VOLLADE_LADEVORG_LESEN` | Percentage of the ratio of full charges to total charges | 1 |
| `0xDF9F` | 2E | `RESET_VERH_VOLLADE_LADEVORG` | Resetting the histogram that is read out with the job: STATUS_VERH_VOLLADE_LADEVORG >> to be carried out when replacing modules | 1 |
| `0xDFA0` | 22 | `ZUSTAND_SPEICHER` | Output of central storage quantities as max., Min. And mean values | 19 |
| `0xDFA1` | 22 | `HIS_ERR_LIM_SPANNUNG` | Output of the maximum dwell time in voltage error limit classes across all modules in minutes. At temperatures <-10 ° C, the voltage error limit changes depending on the temperature. | 6 |
| `0xDFAE` | 22 | `HIS_SOC_MAX_MIN` | Job has not been requested for SME_03 since I001_14-03-490 and is therefore not implemented from now on. Output of the minimum and maximum MIN nominal SoC that occurs over the life of the vehicle. | 2 |
| `0xDFAF` | 2E | `RESET_HIS_SOC_MAX_MIN` | Job has not been requested for SME_03 since I001_14-03-490 and is therefore not implemented from now on. Resetting to the initial value of the minimum (= 255) and maximum (= 0) MIN nominal SoC that occurs over the life of the vehicle. Effect on the return of STATUS_HIS_SOC_MAX_MIN | 1 |
| `0xDFC9` | 2E;22 | `LPA_HVS_LD_INT` | Setting the new HVS self-protection current integral value / reading the current HVS self-protection current integral value and returning the project-specific current and current integral limits | 6 |
| `0xDFE1` | 22 | `STATUS_HV_SPEICHER_ID` | Reading out the storage identification number of the HV storage | 2 |
| `0xDFE2` | 22 | `SYMMETRIERBAND` | Information about the last successful balancing process and the last no-load SoCs | 8 |
| `0xE4E1` | 2E | `RESET_KUEHLERBRUCH` | Reset of the effects of a detected cooler breakage after a service measure | 1 |
| `0xE50D` | 22 | `GW_INFO_SCHNELLLADEN` | Provides warranty-relevant information on the share of fast charging in the total energy throughput of the storage facility at different temperatures. | 5 |
| `0xE540` | 22 | `CODIERVARIABLEN_HV_SPEICHER` | Reads out all coding variables with manipulation potential | 4 |
| `0xE5EC` | 2E;22 | `SOH_OFFSET` | Correction variables with which the functions for capacity aging are corrected during operation. | 4 |
| `0xE5EF` | 2E | `ANZAHL_DEFEKTE_SICHERUNG_RESET` | Resets the number of defective fuses since all modules were last replaced | 2 |
| `0xE5F0` | 2E | `ANZAHL_DEFEKTE_SICHERUNG_INKREMENT` | Increments the number of defective fuses since all modules were last replaced | 2 |
| `0xE5F1` | 22 | `ANZAHL_DEFEKTE_SICHERUNG` | Number of defective fuses since all modules were last replaced | 1 |
| `0xE5F2` | 22 | `HVOFF_VOLTAGES` | Status job to analyze the voltage drop after parking the vehicle. In connection with the cell indices and status signals of the symmetry requirement, this enables a collection of indices for defective or particularly weak cells in the module network. | 83 |
| `0xE5F3` | 22 | `RB_SOH_KAPATEST_ERW` | Extension of the return of the results of the last 3 HVS offboard capacity tests (ring memory) | 27 |
| `0xE5F4` | 22 | `CPI_ANALYSE` | Returns a data packet with the most critical relative temperature deviation since the last reset (drag pointer). A data package contains the relevant measured values for data entry for the CPI diagnosis. | 10 |
| `0xE5FA` | 22 | `KAPAZITAETSTEST_ASYMMETRIE_POTENTIAL` | Return of sizes for the asymmetry potential of the memory that were determined as part of a capacity determination (offboard capacity test). The cell and module index of the cell that potentially has the lowest capacity, as well as the additional capacity range of this cell (in percent), which can potentially be made usable by balancing the memory, are output. | 3 |
| `0xF190` | 22;2E | `VIN` | Chassis number | 2 |
| `0xF500` | 31 | `_HEIZUNG` | switch on the heating | 2 |
| `0xAD77` | 31 | `ALTERUNG_KAPAZITAET_MODUL_LESEN` | Read the aging of module x, based on the capacity ratio (capacity ratio = (C_current / C_nominal(new)) * 100; 100% = new condition, decreases with aging) *(2012 SGBD only)* | 2 |
| `0xAD78` | 31 | `ALTERUNG_INNENWIEDERSTAND_MODUL_LESEN` | Read the aging of module x, based on the internal resistance ratio (ratio = (R_new / R_current) * 100; 100% = new condition, decreases with aging) *(2012 SGBD only)* | 2 |
| `0xAD79` | 31 | `ZELLPACK_SOH_LESEN` | Reading out the aging status (e.g. defect, etc.) of module x *(2012 SGBD only)* | 2 |
| `0xDD6F` | 22;2E | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: Closed or open / close or open *(2012 SGBD only)* | 2 |
| `0xDDC1` | 2E | `CSC_IDS` | Hardware IDs of the individual CSCs (Cell Supervisory Circuit) *(2012 SGBD only)* | 1 |
| `0xDF61` | 2E | `SOC_GRENZE_OBEN` | Opening/resetting the upper SOC limit *(2012 SGBD only)* | 2 |
| `0xDF82` | 2E | `RESET_SBOX` | Input for resetting the S-BOX parameters *(2012 SGBD only)* | 1 |
| `0xF190` | 22 | `VIN` | 17-digit vehicle identification number, 00000000000000000 if no VIN is present (virgin ECU). Note: the result value 00000000000000000 is returned if the CAS returns 0xFF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF in the response telegram. *(2012 SGBD only)* | 1 |

## BMW i3 / i3s (I01) — EME (Drive inverter + DC/DC)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x1060` | 31 | `FS_LOESCHEN_PERMANENT` | Job to delete the permanent DTCs | 0 |
| `0x1061` | 31 | `FEHLERSPEICHER_ENDE_WERKSABLAUF` | Deletion of individual errors and permanent DTCs prevented | 1 |
| `0x4009` | 22 | `AKS_DIAG_STATUS_INFO` | Query of AE status bits for diagnosis and assignment of AKSs | 16 |
| `0x400C` | 2E | `AE_SN_SETZEN` | serial number | 4 |
| `0x400D` | 2E | `AE_HWCAL_SETZEN` | Set hardware calibration data of the AE The serial number cannot be set (own job _steuern_sn_etzen) !!! | 6 |
| `0x400E` | 2E | `AE_HWCAL_FLASHEN` | Writes the HWCALs of a certain block into the flash | 2 |
| `0x400F` | 2E | `AE_HWCAL_MODE` | Bring the SG into HWCAL Flash mode | 1 |
| `0xADC0` | 31 | `STEUERN_START_LADEN` | Request charging start | 1 |
| `0xADC1` | 31 | `STEUERN_STOP_LADEN` | Request charging stop | 1 |
| `0xADC4` | 31 | `REX_ON_OFF` | Switching on / off the range extender combustion engine | 2 |
| `0xADEB` | 31 | `LAST_HISTOGRAMM_EMASCHINE` | Read out histogram with speed-torque ranges of the electrical machine | 13 |
| `0xADF1` | 31 | `EME_DCDC_WANDLER` | Control or read the status of the DC / DC converter | 8 |
| `0xADF2` | 31 | `EME_HV_SYSTEM_ON_OFF` | Run the HV system up / down | 2 |
| `0xADF4` | 31 | `EME_AKS_EMK` | Command the electric machine in the AKS: 0 - Control on EME-SW; 1 - AKS E-machine requested | 2 |
| `0xADF6` | 31 | `AE_ROTORLAGESENSOR_ANLERNEN` | Teaching in the rotor position sensor (TA-EOL STEUERN) | 6 |
| `0xADF8` | 31 | `AE_KLASSIERUNG` | Reading out the speed / torque classification data | 65 |
| `0xADF9` | 31 | `AE_DCDC_HISTOGRAMM` | Reading the requested histogram of the DCDC converter | 11 |
| `0xADFC` | 31 | `LADEHISTORIE_SATZ_LESEN` | Reads out the records of the loading history. | 30 |
| `0xADFE` | 31 | `KLASSIERUNG_ZUG_SCHUB` | Read out the current data of the pull / push LW classification | 7 |
| `0xAF42` | 31 | `LADEGERAET_HISTOGRAMM_LESEN` | Read out the histograms of the charger | 7 |
| `0xDDF6` | 22 | `EME_DCDC_LV` | Voltage / current DCDC (12V vehicle electrical system) at the B + bolt | 2 |
| `0xDE00` | 22 | `EME_HVPM_DCDC_ANSTEUERUNG` | Return values from the HVPM for DCDC control | 16 |
| `0xDE02` | 22 | `EME_HVPM_HV_SYSTEM_ON_OFF` | High-voltage system on / off (HVPM 2013) | 7 |
| `0xDE04` | 22 | `EME_HVPM_ENERGIEBORDNETZ_2` | Number of times the vehicle was ready to drive in the SOC area | 14 |
| `0xDE06` | 22 | `EME_HVPM_PKOR` | HVPM performance coordinator | 59 |
| `0xDE08` | 2E | `EME_HVPM_INFOSPEICHER_PKOR_LOESCHEN` | All information memories of the diagnostic job STATUS_HVPM_PKOR are set to zero. | 1 |
| `0xDE09` | 2E | `EME_HVPM_INFOSPEICHER_STRZLR_LOESCHEN` | Deleting the information memory: HVPM_DCDC_ALS | 1 |
| `0xDE0A` | 2E | `EME_HVPM_INFOSPEICHER_SPMON_LOESCHEN` | Deleting the information memory HVPMP (SPMON) | 1 |
| `0xDE0C` | 22 | `EME_HVIL_GESAMT` | Reading out the HVIL status in the EME; if HVIL is interrupted, then not ok | 1 |
| `0xDE0E` | 22 | `EME_ANSTEUERUNG_ELUP` | Current switching status ELUP (0 - off; 1 - on) | 1 |
| `0xDE19` | 2E;22 | `EME_ELUP` | Number of brake actuations, running time and starts of the ELUP | 6 |
| `0xDE1C` | 22 | `EME_HVPM_DCDC_ALS` | HVPM DCDC ALS | 4 |
| `0xDE2D` | 22 | `AE_CPLD_VERSION` | CPLD version | 1 |
| `0xDE39` | 22 | `AE_SYSTEMLEISTUNG_INV_EM` | Evaluation of the system performance of the INV & EM network. | 29 |
| `0xDE3E` | 2E;22 | `EME_HVPM_KONFIGURATION_LADEEINSTELLUNG` | Configuration loading or low-cost loading as a valid interface | 2 |
| `0xDE69` | 22;2E | `AE_PARKSPERRE_VARIANTE` | Parking lock variant | 2 |
| `0xDE6E` | 22 | `AE_LSC_LADEN_2` | Last State Call Load (Extended) Feedback on the charging process | 41 |
| `0xDE71` | 22 | `AE_CHARGE_ENABLE` | Statement about the granting of loading clearance | 1 |
| `0xDE74` | 22 | `AE_PARKSPERRE_SENSOREN` | Parking lock status sensors | 2 |
| `0xDE75` | 22 | `AE_HV_SPANNUNG_LESEN` | Values of all intermediate circuit voltages | 5 |
| `0xDE76` | 22 | `AE_PARKSPERRE_SW` | Parking lock software status | 1 |
| `0xDE77` | 2E | `AE_PARKSPERRE` | Parking lock status / parking lock engaged | 1 |
| `0xDE78` | 2E;22 | `AE_PARKSPERRE_EINLERNEN` | Parking lock / teaching in parking lock | 4 |
| `0xDE79` | 22 | `AE_PARKSPERRE_POSITION` | Current position of the parking lock | 1 |
| `0xDE7A` | 2E;22 | `AE_PARKSPERRE_POSITIONEN` | Writing the parking lock positions or returning the learned parking lock positions | 4 |
| `0xDE7B` | 22 | `AE_PARKSPERRE_STROM` | Current parking lock actuator current | 1 |
| `0xDE7C` | 22 | `AE_PARKSPERRE_SPANNUNGEN` | Parking lock tension | 2 |
| `0xDE7D` | 22 | `AE_ROHSIG_AUSGANG` | Raw signals output pins | 4 |
| `0xDE7E` | 22 | `AE_ROHSIG_EINGANG_SENS_ELUP_BUDS` | Raw signals output pins sensors ELUP, BUDS | 2 |
| `0xDE7F` | 22 | `AE_ROHSIG_EINGANG_SENS_EM_INV` | Raw signals sensors / inputs for e-machines / converters | 10 |
| `0xDE80` | 22 | `AE_ROHSIG_EINGANG_SENS_PARKSPERRE` | Raw signals sensors / inputs parking lock | 3 |
| `0xDE81` | 22 | `AE_ROHSIG_EINGANG_SENS_SG` | Raw signals sensors / inputs control unit | 3 |
| `0xDE82` | 22 | `AE_ROHSIG_EINGANG_SENS_SLE` | Raw signals sensors / inputs SLE | 3 |
| `0xDE83` | 22 | `AE_ROHSIG_EINGANG_SENS_DCDC` | Raw signals sensors / inputs DC / DC converter | 3 |
| `0xDE84` | 22 | `AE_BETRIEBSZUSTAND_SLE` | Operating modes SLE | 6 |
| `0xDE85` | 22 | `AE_SLE_LEISTUNG` | Power values intermediate circuit of the SLE | 3 |
| `0xDE86` | 22 | `AE_SLE_SPANNUNG` | AC and DC voltages SLE | 3 |
| `0xDE87` | 22 | `AE_SLE_STROM` | calibrated SLE transformer current | 1 |
| `0xDE88` | 22 | `AE_SPANNUNG_KLEMME30B` | current voltage at KL30B | 1 |
| `0xDE89` | 22 | `AE_STROM_DCDC` | DC / DC converter currents | 5 |
| `0xDE8A` | 22 | `AE_STROM_EMASCHINE` | E-machine / converter currents | 5 |
| `0xDE8C` | 22 | `AE_TEMP_LE` | Temperatures control unit drive electronics | 15 |
| `0xDE92` | 22 | `AE_ZUSTAND_1_DCDC` | DC / DC converter status | 3 |
| `0xDE93` | 2E;22 | `AE_ELUP` | Current status ELUP or activate / deactivate ELUP | 5 |
| `0xDE95` | 2E | `AE_PARKSPERRE_NVRAM_LOESCHEN` | Deletes NV-RAM data from the parking lock | 1 |
| `0xDE96` | 22 | `AE_ZUSTAND_DCDC_FEHLERBILD` | Return of active / inactive errors DC / DC converter | 1 |
| `0xDE9E` | 22 | `STATUS_CONNECTED_DRIVE` | Information about Connected Drive | 10 |
| `0xDEA1` | 2E;22 | `LADEHISTORIE` | Reading / deleting the charging history | 109 |
| `0xDEA5` | 22 | `AE_BUDS` | Brake vacuum sensor value | 1 |
| `0xDEA6` | 22 | `AE_TEMP_EMASCHINE` | Value of the current temperatures of the e-machine in degrees Celsius | 2 |
| `0xDEA7` | 22 | `AE_ELEKTRISCHE_MASCHINE` | Reading out the speed, torque and operating mode of the electric machine | 4 |
| `0xDEA9` | 22 | `AE_ZUSTAND_2_DCDC` | Various statuses returned from the DCDC converter | 1 |
| `0xDEAE` | 2E;22 | `LADEHISTOGRAMM` | Reading / deleting the histogram and counter of all charging processes (electric vehicle and plug-in hybrid) | 27 |
| `0xDEB0` | 22 | `AE_PARKSPERRE_VERSION` | Return of the current version of the parking lock software | 2 |
| `0xDEB1` | 2E;22 | `AE_ROTORLAGESENSOR` | Direct writing or reading of the resolver offset angle | 3 |
| `0xDEB2` | 2E | `AE_DCDC_TEMPHISTOGRAMM_LESEN` | Read out temperature histograms DCDC / reset temperature histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB3` | 2E | `AE_DCDC_LEISTUNGSHISTOGRAMM` | Read out power histograms DCDC converter / reset power histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB4` | 2E | `AE_RESET_TEMP_MIN_MAX` | Resetting the minimum and maximum temperature of the DC / DC converter (0 = no reset; 1 = reset) | 1 |
| `0xDEB6` | 2E | `AE_ROTORLAGESENSOR_RESET` | Resetting the resolver offset angle | 1 |
| `0xDEB7` | 2E | `AE_KLASSIERUNG_LOESCHEN` | Deletion of the entire classification data | 1 |
| `0xDEBC` | 22 | `AE_CTRL_VERSION` | Controller board version | 1 |
| `0xDEBD` | 22 | `AE_SPANNUNG_DCDC` | DC / DC voltage low-voltage side | 1 |
| `0xDEBE` | 22 | `AE_SPANNUNG_LE` | Internal voltages of the power electronics | 7 |
| `0xDEBF` | 22 | `AE_SYSSTATE` | Internal status states of the control unit | 4 |
| `0xDEC2` | 22 | `SPANNUNG_ELUP` | Voltage level at the ELUP output of the EME | 1 |
| `0xDEC3` | 22 | `STROM_ELUP` | Voltage level at the ELUP output of the EME | 1 |
| `0xDED1` | 2E;22 | `REX_RESONANZ` | Reading out the learned resonance ranges / teaching-in the resonance ranges | 8 |
| `0xDEDD` | 22 | `AE_FAHRSTUFE` | current actual position of the drive train (PRND) | 1 |
| `0xDEDE` | 22 | `AE_LSC_LADEN` | Feedback on the charging process | 29 |
| `0xDEDF` | 2E;22 | `UI_DERATING_EM1` | Read out or reset UI derating values from E-machine 1 | 31 |
| `0xDEE0` | 2E;22 | `UI_DERATING_EM2` | Read out or reset UI derating values from e-machine 2 | 31 |
| `0xDEE5` | 2E | `KLASSIERUNG_ZUG_SCHUB_LOESCHEN` | Deletion of the entire push / pull load cycle classification | 1 |
| `0xDEED` | 22 | `HISTOGRAMM_ANTRIEB` | History values for drive | 45 |
| `0xDEEE` | 2E;22 | `REX_HISTOGRAMM` | Reading out or resetting the histogram from the range extender | 12 |
| `0xDEEF` | 22 | `HISTOGRAMM_DEGRADATION` | Historical values degradation | 40 |
| `0xDEFB` | 22 | `AUTOP_SBW` | Frequency counter for the reasons for Auto-P and SW version shift-by-wire | 7 |
| `0xDEFF` | 22 | `FAHRSTUFEN_ZAEHLER_SBW` | Frequency counter of speed step changes | 12 |
| `0xDF1F` | 22;2E | `VERBAUKENNUNG_UCX_RUECKSETZEN` | Resetting the installation recognition of the AC-UCX control device (job duration 1s; status persistent, only via control device_reset or falling asleep) | 2 |
| `0xDF45` | 2E | `LADESTROM_EINSTELLUNG` | Setting current limits | 2 |
| `0xDF49` | 22 | `HISTOGRAMM_LADEKOORDINATOR` | Charge coordinator histograms | 24 |
| `0xDF4D` | 22 | `INVERTER_HISTOGRAMM` | Reading out the calculated lifetime data of the inverter | 5 |
| `0xDF50` | 2E;22 | `LADEMODUS_WERK` | Setting and reading out the factory charging mode (charging to the specified SOC) | 4 |
| `0xDF51` | 2E | `ELUP_DATEN_RESET` | Reset of all statistical data of the ELUP | 1 |
| `0xDF52` | 2E;22 | `ROTORLAGESENSOR_WINKELCODE` | Setting and reading out the resolver offset angle after decryption | 3 |
| `0xDF58` | 22 | `INVERTER_RBM_INFO` | RBM information for the non-running inverter diagnosis in I01 and I12 | 18 |
| `0xDF59` | 22 | `DCDC_RBM_INFO` | RBM information for the discontinuous DC / DC converter diagnosis in I01 and I12 | 24 |
| `0xDF5A` | 22 | `LADEGERAET_RBM_INFO` | RBM information for the discontinuous charger diagnosis at I01 and I12 | 72 |
| `0xDF5B` | 22 | `LIEFERANT_TRACE_NUMMER` | 29 bytes SG manufacturer trace number | 1 |
| `0xDF5D` | 2E | `LAST_HISTOGRAMM_EMASCHINE_RESET` | Histogram with speed-torque ranges of the electrical machine | 1 |
| `0xDFB3` | 2E;22 | `LADEGERAET_KONFIGURATION` | Configuration of built-in charger type (s) | 2 |
| `0xDFB4` | 2E | `LADEGERAET_HISTOGRAMM_RESET` | Resetting the histograms from the charger | 1 |
| `0xDFB5` | 22 | `LADEGERAET_TEMPERATUR_HISTOGRAMM` | Temperature histograms of the charging electronics (SLE) present within the drive electronics (AE) | 18 |
| `0xDFB7` | 22 | `LADEGERAET_HV_UEBERSTROM` | Charger overcurrent meter based on HV DC current sensor raw value | 1 |
| `0xDFCE` | 22 | `EMASCHINE_MAX_DREHZAHL` | Reading out the absolute time in the critical electric machine speed range | 2 |
| `0xDFD0` | 22 | `LAST_HISTOGRAMM_EMASCHINE_LESEN` | Reading out the histograms of the electric machine (speed, torque, change of sign of the torque) | 120 |
| `0xE52F` | 22 | `RATE_BASED_MONITORING` | RBM data on discontinuous diagnoses including dependent secondaries. | 426 |
| `0xE5FE` | 22 | `LADEKOORDINATOR_INTERFACE` | Interfaces from the charging coordinator to HVPM and chargers | 55 |
| `0xE5FF` | 22 | `DCDC_MESSGROESSEN_KOMPLETT` | Status of all available DCDC measured values for both PKR2 and non-PKR2 software | 35 |
| `0xF000` | 31 | `NV_FLASH_PRUEFEN` | Check NV flash for read errors | 6 |
| `0xF001` | 31 | `RBM_TEST` | Start of the rate based monitoring test | 12 |
| `0xF010` | 31 | `AE_HWCAL_LESEN` | Reading out the HWCALs using the block number and processor | 6 |
| `0xF011` | 31 | `AE_RESETINFO_LESEN` | Reading out the reset info from the flash | 0 |
| `0xF012` | 31 | `AKS_DIAG_STATUS_SELECT` | Query of AE status bits for diagnosis and assignment of AKSs | 19 |
| `0xF050` | 31 | `AE_FREILAUF_MODUS` | Free running mode | 1 |
| `0xADC9` | 31 | `AE_EWP` | Actuate and read out the electric coolant pump (actuation possible only when AE temperature is below threshold, house keeping not active, EWP not switched off, and manual speed control deactivated) *(2012 SGBD only)* | 5 |
| `0xDE03` | 22 | `EME_HVPM_ENERGIEBORDNETZ` | Return values of the HVPM for HV energy and cell voltages *(2012 SGBD only)* | 34 |
| `0xDE18` | 22 | `EME_HVPM_SPANNUNGSFREIHEIT` | Info memory for the de-energized state of the high-voltage system (monitored by HVPM) *(2012 SGBD only)* | 40 |
| `0xDE19` | 22 | `EME_ELUP` | Number of brake actuations, running time and starts of the ELUP *(2012 SGBD only)* | 3 |
| `0xDE78` | 22;2E | `AE_PARKSPERRE_EINLERNEN` | Parking lock / teaching in parking lock *(2012 SGBD only)* | 3 |
| `0xDE7A` | 22 | `AE_PARKSPERRE_POSITIONEN` | Return learned parking lock positions *(2012 SGBD only)* | 2 |
| `0xDE8B` | 22;2E | `AE_STROM_MAX` | Maximum measured currents since last reset or reset of values *(2012 SGBD only)* | 9 |
| `0xDEA0` | 22 | `STATUS_TSR_LADEN` | All return values regarding TSR charging *(2012 SGBD only)* | 130 |
| `0xDEA1` | 2E | `LADEHISTORIE` | Reading / deleting the charging history *(2012 SGBD only)* | 1 |
| `0xDEB1` | 2E | `AE_ROTORLAGESENSOR_SCHREIBEN` | Direct write of the resolver offset angle *(2012 SGBD only)* | 1 |
| `0xDEB5` | 22 | `AE_PIC_SW_VERSION` | Returns current version of the PIC software *(2012 SGBD only)* | 2 |
| `0xDEDF` | 22;2E | `UI_DERATING_EM1` | Read out or reset UI derating values from E-machine 1 *(2012 SGBD only)* | 6 |
| `0xDEE0` | 22;2E | `UI_DERATING_EM2` | Read out or reset UI derating values from e-machine 2 *(2012 SGBD only)* | 6 |

## BMW i3 / i3s (I01) — EME (Drive electronics (alternate SGBD EME_I1))

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xADF4` | 31 | `EME_AKS_EMK` | Command the electric machine in the AKS: 0 - Control on EME-SW; 1 - AKS E-machine requested | 2 |
| `0xADF6` | 31 | `AE_ROTORLAGESENSOR_ANLERNEN` | Teaching in the rotor position sensor (TA-EOL STEUERN) | 6 |
| `0xADF8` | 31 | `AE_KLASSIERUNG` | Reading out the speed / torque classification data | 44 |
| `0xADF9` | 31 | `AE_DCDC_HISTOGRAMM` | Reading the requested histogram of the DCDC converter | 11 |
| `0xDDF6` | 22 | `EME_DCDC_LV` | Voltage / current DCDC (12V vehicle electrical system) at the B + bolt | 2 |
| `0xDE0C` | 22 | `EME_HVIL_GESAMT` | Reading out the HVIL status in the EME; if HVIL is interrupted, then not ok | 1 |
| `0xDE2D` | 22 | `AE_CPLD_VERSION` | CPLD version | 1 |
| `0xDE71` | 22 | `AE_CHARGE_ENABLE` | Statement about the granting of loading clearance | 1 |
| `0xDE74` | 22 | `AE_PARKSPERRE_SENSOREN` | Parking lock status sensors | 2 |
| `0xDE75` | 22 | `AE_HV_SPANNUNG_LESEN` | Values of all intermediate circuit voltages | 5 |
| `0xDE76` | 22 | `AE_PARKSPERRE_SW` | Parking lock software status | 1 |
| `0xDE77` | 2E | `AE_PARKSPERRE` | Parking lock status / parking lock engaged | 1 |
| `0xDE78` | 2E;22 | `AE_PARKSPERRE_EINLERNEN` | Parking lock / teaching in parking lock | 3 |
| `0xDE79` | 22 | `AE_PARKSPERRE_POSITION` | Current position of the parking lock | 1 |
| `0xDE7A` | 22 | `AE_PARKSPERRE_POSITIONEN` | Return learned parking lock positions | 2 |
| `0xDE7B` | 22 | `AE_PARKSPERRE_STROM` | Current parking lock actuator current | 1 |
| `0xDE7C` | 22 | `AE_PARKSPERRE_SPANNUNGEN` | Parking lock tension | 2 |
| `0xDE7D` | 22 | `AE_ROHSIG_AUSGANG` | Raw signals output pins | 4 |
| `0xDE7E` | 22 | `AE_ROHSIG_EINGANG_SENS_ELUP_BUDS` | Raw signals output pins sensors ELUP, BUDS | 2 |
| `0xDE7F` | 22 | `AE_ROHSIG_EINGANG_SENS_EM_INV` | Raw signals sensors / inputs for e-machines / converters | 13 |
| `0xDE80` | 22 | `AE_ROHSIG_EINGANG_SENS_PARKSPERRE` | Raw signals sensors / inputs parking lock | 3 |
| `0xDE81` | 22 | `AE_ROHSIG_EINGANG_SENS_SG` | Raw signals sensors / inputs control unit | 5 |
| `0xDE83` | 22 | `AE_ROHSIG_EINGANG_SENS_DCDC` | Raw signals sensors / inputs DC / DC converter | 3 |
| `0xDE88` | 22 | `AE_SPANNUNG_KLEMME30B` | current voltage at KL30B | 1 |
| `0xDE89` | 22 | `AE_STROM_DCDC` | DC / DC converter currents | 6 |
| `0xDE8B` | 22;2E | `AE_STROM_MAX` | Maximum measured currents since last reset or reset of values | 9 |
| `0xDE8C` | 22 | `AE_TEMP_LE` | Temperatures control unit drive electronics | 21 |
| `0xDE92` | 22 | `AE_ZUSTAND_1_DCDC` | DC / DC converter status | 3 |
| `0xDE93` | 22;2E | `AE_ELUP` | Current status ELUP or activate / deactivate ELUP | 5 |
| `0xDE94` | 2E | `AE_PARKSPERRE_MAGNET` | Switch on park lock solenoid | 1 |
| `0xDE95` | 2E | `AE_PARKSPERRE_NVRAM_LOESCHEN` | Deletes NV-RAM data from the parking lock | 1 |
| `0xDE96` | 22 | `AE_ZUSTAND_DCDC_FEHLERBILD` | Return of active / inactive errors DC / DC converter | 1 |
| `0xDEA5` | 22 | `AE_BUDS` | Brake vacuum sensor value | 1 |
| `0xDEA6` | 22 | `AE_TEMP_EMASCHINE` | Value of the current temperatures of the e-machine in degrees Celsius | 2 |
| `0xDEA7` | 22 | `AE_ELEKTRISCHE_MASCHINE` | Reading out the speed, torque and operating mode of the electric machine | 4 |
| `0xDEA9` | 22 | `AE_ZUSTAND_2_DCDC` | Various statuses returned from the DCDC converter | 1 |
| `0xDEB0` | 22 | `AE_PARKSPERRE_VERSION` | Return of the current version of the parking lock software | 2 |
| `0xDEB1` | 2E | `AE_ROTORLAGESENSOR_SCHREIBEN` | Direct write of the resolver offset angle | 1 |
| `0xDEB2` | 2E | `AE_DCDC_TEMPHISTOGRAMM_LESEN` | Read out temperature histograms DCDC / reset temperature histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB3` | 2E | `AE_DCDC_LEISTUNGSHISTOGRAMM` | Read out power histograms DCDC converter / reset power histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB4` | 2E | `AE_RESET_TEMP_MIN_MAX` | Resetting the minimum and maximum temperature of the DC / DC converter (0 = no reset; 1 = reset) | 1 |
| `0xDEB5` | 22 | `AE_PIC_SW_VERSION` | Returns current version of the PIC software | 2 |
| `0xDEB6` | 2E | `AE_ROTORLAGESENSOR_RESET` | Resetting the resolver offset angle | 1 |
| `0xDEB7` | 2E | `AE_KLASSIERUNG_LOESCHEN` | Deletion of the entire classification data | 1 |
| `0xDEBC` | 22 | `AE_CTRL_VERSION` | Controller board version | 1 |
| `0xDEBD` | 22 | `AE_SPANNUNG_DCDC` | Voltages DCDC converter | 2 |
| `0xDEBE` | 22 | `AE_SPANNUNG_LE` | Internal voltages of the power electronics | 9 |
| `0xDEBF` | 22 | `AE_SYSSTATE` | Internal status states of the control unit | 4 |
| `0x400C` | 2E | `AE_SN_SETZEN` | serial number | 4 |
| `0x400D` | 2E | `AE_HWCAL_SETZEN` | Set hardware calibration data of the AE The serial number cannot be set (own job _steuern_sn_etzen) !!! | 5 |
| `0x400E` | 2E | `AE_HWCAL_FLASHEN` | Writes the HWCALs of a certain block into the flash | 2 |
| `0x400F` | 2E | `AE_HWCAL_MODE` | Bring the SG into HWCAL Flash mode | 1 |
| `0xF010` | 31 | `AE_HWCAL_LESEN` | Reading out the HWCALs using the block number and processor | 5 |
| `0xF011` | 31 | `AE_RESETINFO_LESEN` | Reading out the reset info from the flash | 13 |
| `0xF050` | 31 | `AE_FREILAUF_MODUS` | Free running mode | 1 |

## BMW i3 / i3s (I01) — KLE (On-board charger (UCX2))

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xAF43` | 31 | `FLASH_DSPS` | Programming of DSP | 1 |
| `0xDE84` | 22 | `BETRIEBSZUSTAND_LADEGERAET` | Operating modes charger | 11 |
| `0xDE85` | 22 | `LADEGERAET_LEISTUNG` | Power values intermediate circuit of the charger | 3 |
| `0xDE86` | 22 | `LADEGERAET_SPANNUNG` | AC and DC voltages charger | 7 |
| `0xDE87` | 22 | `LADEGERAET_STROM` | AC and DC currents charger | 7 |
| `0xDF25` | 22 | `AC_PHASENANZAHL` | Status of the number of AC phases | 1 |
| `0xDFB0` | 22 | `LADEGERAET_LADEDAUER` | Information on the charging time | 3 |
| `0xDFB1` | 22 | `LADEGERAET_TEMPERATUREN` | Reading out temperatures | 10 |
| `0xDFB4` | 22 | `LADEGERAET_LEISTUNG2` | Power values for second charger (multi-phase charging) | 3 |
| `0xDFB6` | 22 | `LADEGERAET_LADE_HISTOGRAMM` | Charge histogram related to temperature and power | 10 |
| `0xDFB7` | 22 | `LADEGERAET_LADE_HISTOGRAMM2` | Charging histogram relating to temperature and power for a second charger (multi-phase charging). | 10 |
| `0xDFB8` | 22 | `LADEGERAET_LADEDAUER2` | Information on the charging time for a second charger (multi-phase charging) | 3 |
| `0xDFB9` | 22 | `UMSCHALTMATRIX` | Switching matrix (multi-phase charging): number of switching cycles and state of the switches | 8 |
| `0xDFBA` | 22 | `LADEGERAET_SPANNUNG2` | AC and DC voltages for second charger (multi-phase charging) | 7 |
| `0xDFBB` | 22 | `LADEGERAET_STROM2` | Charger currents for second charger (multi-phase charging) | 7 |
| `0xDFBC` | 22 | `BETRIEBSZUSTAND_LADEGERAET2` | Operating modes charger for second charger (multi-phase charging) | 11 |
| `0xDFBD` | 22 | `LADEDAUER_LADEART` | Charging time for different charging types | 6 |
| `0xF000` | 31 | `FLASH_DSPS` | RID used to flash DSPs | 1 |

## BMW i3 / i3s (I01) — LIM (Charge interface module)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x2541` | 22 | `STATUS_CALCVN` | Read out Cal-ID (Calibration-ID) and CVN (Calibration Verification Number). (OBD scopes) Byte layout: 20 bytes long 00-15 = STAT_CALID_WERT 16-19 = STAT_CVN_EINH as Hex unit32 in Intel format | 2 |
| `0xDB0E` | 2E;22 | `ZV_LADESTECKER_CN` | Actuator AC plug lock (China front) | 3 |
| `0xDB0F` | 22 | `LADESTECKDOSE_TEMPERATUR` | Temperature of the DC charging connection in ° C (China) | 1 |
| `0xDE6B` | 22;2E | `LADEN_HOSPITALITY_FUNKTION` | Hospitality function (automatic unlocking of the charging plug at the end of the charging process). | 2 |
| `0xDEF0` | 22;2E | `ZV_LADESTECKER` | Status and control of charging plug (depending on plug type and market) 0 = unlocked, 1 = locked | 3 |
| `0xDEF1` | 22;2E | `ZV_LADEKLAPPE` | Status or control loading flap (0 = unlocked, 1 = locked) | 3 |
| `0xDEF2` | 22 | `LADEBEREITSCHAFT_LIM` | Ready to charge (HW line), (1 = yes, 0 = no) sent from LIM to SLE | 1 |
| `0xDEF3` | 22;2E | `LED_LADESTATUS` | Status or control LED for charging status (RGB light ring) | 2 |
| `0xDEF4` | 22;2E | `LED_SUCHBELEUCHTUNG` | Status or activation of the LED for search lighting (0 = not activated, 1 = activated) - only for separate DC charging socket | 2 |
| `0xDEF5` | 22 | `PROXIMITY` | Current status of the proximity | 2 |
| `0xDEF6` | 22 | `PILOTSIGNAL` | current data of the pilot signal about the charging current | 6 |
| `0xDEF7` | 22 | `LADESCHNITTSTELLE_DC_TEPCO` | Status of the batch control lines | 4 |
| `0xDEF8` | 22 | `DC_SCHUETZ_SCHALTER` | Contactor switch status (DC charging) | 1 |
| `0xDEF9` | 22 | `DC_SCHUETZ_SPANNUNG_EINGANG` | Voltage at the input of the relay box (contactors) for DC charging | 2 |
| `0xDEFA` | 22 | `DC_PINABDECKUNG_COMBO` | State of the DC pin cover for combo socket (0 = closed, 1 = open) | 1 |
| `0xDEF0` | 2E;22 | `ZV_LADESTECKER` | Status and control of charging plug (depending on plug type and market) 0 = unlocked, 1 = locked *(2012 SGBD only)* | 3 |
| `0xDEF3` | 2E;22 | `LED_LADESTATUS` | Status or control LED for charging status (RGB light ring) *(2012 SGBD only)* | 2 |
| `0xDEF4` | 2E;22 | `LED_SUCHBELEUCHTUNG` | Status or activation of the LED for search lighting (0 = not activated, 1 = activated) - only for separate DC charging socket *(2012 SGBD only)* | 2 |
| `0xF001` | 2E | `_RGB_LED_RAW_CTRL` | Raw control of RGB LED *(2012 SGBD only)* | 5 |
| `0xF002` | 2E | `_IP_OF_LIM` | Writes IP of the LIM *(2012 SGBD only)* | 9 |
| `0xF003` | 2E | `_IP_OF_EVSE` | Writes IF of the EVSE *(2012 SGBD only)* | 9 |

## BMW i3 / i3s (I01) — IHX (Heating/AC, heat pump, HV heater)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xA111` | 31 | `KLAPPENMOTOR_IDENT` | Reading out the manufacturer-specific data of a flap motor. | 4 |
| `0xA11B` | 31 | `EDH_VERRIEGELUNG` | Controlling the protective locking of the eDH. | 2 |
| `0xA11C` | 31 | `WP_BEFUELLUNG` | Switching of the valves for filling the heat pump circuit | 1 |
| `0xA11D` | 31 | `WP_EXP_VENTIL_KALIBRIEREN` | Calibrate the expansion valves | 1 |
| `0xD15D` | 22 | `SITZHEIZUNG_VORNE_TASTER_LINKS` | 0 = button not pressed, 1 = button pressed | 1 |
| `0xD15E` | 22 | `SITZHEIZUNG_VORNE_TASTER_RECHTS` | 0 = button not pressed, 1 = button pressed | 1 |
| `0xD15F` | 22 | `SITZHEIZUNG_VORNE_LED_RECHTS` | Status LED display seat heating, front right | 4 |
| `0xD160` | 22 | `SITZHEIZUNG_VORNE_LED_LINKS` | Status LED display seat heating, front left | 4 |
| `0xD592` | 2E;22 | `FBM_SENS_TASTEN` | FBM sensors | 10 |
| `0xD593` | 2E;22 | `FBM_TASTEN` | FBM buttons | 10 |
| `0xD598` | 2E | `STEUERN_SIGNALMODE` | Sets whether the signals are sent to the outside on the CAN when the control elements are operated (suppressed = Arg 1). Is automatically deactivated when changing terminals (or with Arg. 0) | 1 |
| `0xD599` | 22 | `FBM_TASTEN_VORHANDEN_WERT` | Indicates how many FBM buttons are installed: 0 = no FBM buttons installed, 1 = 1 button installed, 2 = 2 buttons installed, N = n buttons installed, 255 = number unknown | 1 |
| `0xD5A0` | 2E | `STEUERN_SH_TASTEN` | Simulation of the actuation of the buttons for the seat heating. | 2 |
| `0xD859` | 22 | `TEMP_FUSSRAUM_LINKS_WERT` | Temperature sensor | 1 |
| `0xD85A` | 22 | `TEMP_FUSSRAUM_RECHTS_WERT` | Temperature sensor | 1 |
| `0xD85C` | 22 | `TEMP_INNEN_UNBELUEFTET` | Calculated internal temperature | 1 |
| `0xD860` | 22 | `BUS_IN_POTI_SCHICHTUNG_FOND_WERT` | Potentiometer layering base: 0 ... 100% | 1 |
| `0xD866` | 22 | `KONFIGURATION_KLIMA_VORN` | Configuration of the front air conditioning | 7 |
| `0xD868` | 22 | `KAELTEMITTEL_MEDIUM` | Cooling medium: 0 = R134a, 1 = CO2 | 1 |
| `0xD86E` | 2E | `STEUERN_KLAPPENMOTOR_VORN` | Call for activation of the individual stepper motors for any opening | 2 |
| `0xD86F` | 2E;22 | `KLIMA_TASTEN_VORN` | Climate control panel buttons | 32 |
| `0xD875` | 2E | `STEUERN_BEDIENUNG_TEMP` | Simulates the setting of the temperature on the climate control unit. | 2 |
| `0xD877` | 2E | `STEUERN_GEBLAESE` | Control of the blower output stage. | 1 |
| `0xD88D` | 2F | `STEUERN_MOTOREN_KALIBRIERLAUF` | Calibration of the stepper motors. | 0 |
| `0xD88E` | 22 | `SCHRITTMOTOR_FEHLER` | Query the stepper motor error | 4 |
| `0xD88F` | 2F | `STEUERN_SELBSTTEST_SCHRITTMOTOREN` | Call starts the self-test of the stepper motors. All motors are approached to 50% and then checked whether the position has been reached. The result can be queried with the SELFTEST_STRITTMOTOREN service. | 0 |
| `0xD89A` | 2E | `STEUERN_DISPLAY_TESTEN` | Controls the display with bit patterns. | 2 |
| `0xD8A0` | 2E | `ELEKTRISCHER_ZUHEIZER_FRONT` | Job to activate the electrical auxiliary heater without the necessary boundary conditions, such as Energy management, energy distribution algorithm. | 2 |
| `0xD8AA` | 22 | `VORHANDEN_FONDSCHICHTUNG` | 0 = rear stratification potentiometer not available 1 = rear stratification potentiometer available | 1 |
| `0xD8AB` | 22 | `SOLARSENSOR_VORHANDEN` | Solar sensor: 0 = not available / coded; 1 = present / coded | 1 |
| `0xD8AC` | 22 | `AUC_SENSOR_VORHANDEN` | AUC sensor: 0 = not available; 1 = present | 1 |
| `0xD8B5` | 2E;22 | `AUDIO_TASTEN` | Audio control panel buttons | 8 |
| `0xD8C1` | 2E;22 | `LEDS_KLIMA_VORN` | LEDs climate control panel | 20 |
| `0xD8C2` | 22 | `EKK_DREHZAHLERHOEHUNG` | Speed increase EKK 0 = OFF, 1 = ON | 1 |
| `0xD8C3` | 22;2E | `EKMV_DREHZAHL_GEN20` | Speed of refrigerant seal | 3 |
| `0xD8C4` | 22 | `EKMV_ANALOGWERTE_GEN20` | Analog values from refrigerant compressor Gen. 2.0 | 6 |
| `0xD8C5` | 22 | `EKMV_BETRIEBSZUSTAND_GEN20` | Operating states of refrigerant compressor Gen. 2.0 | 1 |
| `0xD8C6` | 2E | `EKMV_RESET_GEN20` | Reset refrigerant compressor gen. 2.0 | 1 |
| `0xD8C7` | 22;2E | `EKMV_AKS_GEN20` | Insulation test eKMV | 2 |
| `0xD8CB` | 22;2E | `EKMV_FREILAUF` | Freewheel eKMV | 2 |
| `0xD8CD` | 22 | `EDH_STATUS` | Status values of electrical instantaneous water heaters | 4 |
| `0xD8CE` | 22 | `KONFIGURATION_KLIMA_PRODUKTLINIE` | Outputs the product line coded in the control unit. See table TAB_KLIMA_PRODUKTLINIE | 1 |
| `0xD8D2` | 22 | `BUS_IN_HV_POWERMANAGEMENT` | The maximum power provided by the HV-PM for the air conditioning. | 2 |
| `0xD8D3` | 22 | `BUS_IN_HV_PM_EDH` | The maximum power provided by the HV-PM for the EDH. | 2 |
| `0xD8D4` | 22 | `BUS_IN_KUEHLMITTELTEMPERATUR` | Engine coolant temperature | 1 |
| `0xD902` | 22 | `SOLLWERT_ELEKTRISCHER_ZUHEIZER_VORN` | Electrical auxiliary heater (PTC or EDH) setpoint in percent 0 - 100% | 1 |
| `0xD904` | 22 | `BUS_OUT_ZUSATZWASSERPUMPE_EIN` | Auxiliary water pump status: 0 = OFF, 1 = ON | 1 |
| `0xD905` | 22 | `TIMER_EINLAUFSCHUTZ` | Determination of the remaining time for the inlet protection. | 2 |
| `0xD90E` | 22 | `SITZHEIZUNG_VORNE_TASTER_VORHANDEN` | 0 = not available 1 = available | 1 |
| `0xD916` | 22 | `VORHANDEN_KOMPRESSORKUPPLUNG` | 0 = compressor clutch not available 1 = compressor clutch available | 1 |
| `0xD918` | 2E;22 | `EINLAUFSCHUTZ_KOMPRESSOR` | Output of the status of the inlet protection for the air conditioning compressor or writing of the new status. This status is only reset after it has been completely run in. | 3 |
| `0xD91A` | 22 | `KLIMA_VORN_LUFTVERTEILUNG_LI_RE` | Output of the status of the air distribution in front. | 2 |
| `0xD91D` | 22 | `BUS_OUT_KLIMAKOMPRESSOR_PWM_WERT` | Signal for requesting the compressor power in PWM | 1 |
| `0xD927` | 2E | `STEUERN_DIAGNOSE_ENDE` | Ends all controls started with diagnosis. | 1 |
| `0xD928` | 22 | `KLIMA_VORN_KLAPPEN_PRG_MITTE` | Automatic flap program: 0 = OFF = manual setting, 1 = ON = AUTO switched on | 1 |
| `0xD92B` | 22 | `KLIMA_VORN_GEBLAESESTUFE_ANZ` | Outputs the display of the current fan speed. | 1 |
| `0xD92C` | 22 | `KLIMA_VORN_OFF_EIN` | Function status air conditioning OFF: 0 = OFF = air conditioning is switched on, LED is off 1 = ON = air conditioning is switched off, LED is on | 1 |
| `0xD92D` | 22 | `KLIMA_VORN_PRG_DEFROST_EIN` | Defrost program: 0 = OFF, 1 = ON | 1 |
| `0xD92E` | 22 | `KLIMA_VORN_PRG_MAX_AC_EIN` | Maximum cooling program: 0 = OFF, 1 = ON | 1 |
| `0xD930` | 22 | `KLIMA_VORN_PRG_AUC_EIN` | Automatic air circulation control: 0 = OFF, 1 = ON | 1 |
| `0xD931` | 22 | `KLIMA_VORN_PRG_UMLUFT_EIN` | Recirculation program: 0 = OFF, 1 = ON | 1 |
| `0xD932` | 22 | `KLIMA_VORN_PRG_HHS_EIN` | Rear window heating: 0 = OFF, 1 = ON | 1 |
| `0xD934` | 22 | `KLIMA_VORN_PRG_AC_EIN` | Climate program: 0 = OFF, 1 = ON | 1 |
| `0xD936` | 22 | `KLIMA_VORN_PRG_KLIMASTIL_MITTE` | Output of the middle soft-intensity setting in steps: 1 - 7 | 1 |
| `0xD939` | 22 | `KLIMA_VORN_PRG_STANDLUEFTEN_EIN` | Independent ventilation program: 0 = OFF, 1 = ON | 1 |
| `0xD93F` | 22 | `KLIMA_VORN_GEBLAESELEISTUNG_WERT` | Fan output of the IHKA fan output stage in%. | 1 |
| `0xD941` | 22 | `KLP_POS_DEFROST_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD942` | 22 | `KLP_POS_BELUEFTUNG_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD947` | 22 | `KLP_POS_FUSSRAUM_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD949` | 22 | `KLP_POS_SCHICHTUNG_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD94A` | 22 | `KLP_POS_SCHICHTUNG_LI_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD94B` | 22 | `KLP_POS_SCHICHTUNG_RE_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD94D` | 22 | `KLP_POS_UMLUFT_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD950` | 22 | `KLP_POS_TEMP_LUFT_FOND_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD953` | 22 | `MOTOR_KALIBRIERLAUF` | Query of the current status of the calibration run of the flap motors. | 22 |
| `0xD954` | 22 | `SELBSTTEST_SCHRITTMOTORE` | Status of stepper motor self-tests: 0 = not started / not requested, 1 = test is currently running, 2 = test successfully completed, 3 = test not completed successfully | 1 |
| `0xD957` | 22 | `TEMP_BELUEFTUNG_LINKS_WERT` | Left ventilation flap temperature If the sensor is defective or unplugged, the value 127 is returned | 1 |
| `0xD958` | 22 | `TEMP_BELUEFTUNG_RECHTS_WERT` | Right ventilation flap temperature If the sensor is defective or unplugged, the value 127 is returned | 1 |
| `0xD959` | 22 | `DRUCKSENSOR_VORHANDEN` | Indicates whether a pressure sensor is installed for R134A: 0 = not available, 1 = available | 1 |
| `0xD95A` | 22 | `VORHANDEN_WASSERVENTIL` | Water valve available | 2 |
| `0xD95C` | 22 | `TEMP_VERDAMPFER_WERT` | Temperature sensor evaporator If the sensor is defective or unplugged, the value 127 is returned | 1 |
| `0xD960` | 22 | `BUS_IN_KOMPRESSORFREIGABE` | Air conditioning compressor release from the engine electronics: 0 = not released, 1 = released | 1 |
| `0xD962` | 22 | `BUS_IN_SOLARSENSOR_WERT` | BUS signal solar sensor | 2 |
| `0xD964` | 22 | `BUS_IN_AUC_SENSOR_WERT` | Load level from the AUC sensor | 1 |
| `0xD966` | 22 | `BUS_IN_BESCHLAGSENSOR_WERT` | PMW signal condensation sensor | 1 |
| `0xD968` | 22 | `BUS_IN_KAELTEMITTELDRUCK_WERT` | Refrigerant pressure for R134A | 1 |
| `0xD96B` | 22 | `BUS_IN_TEMP_AUSSEN_WERT` | Outside temperature | 1 |
| `0xD96D` | 22 | `BESCHLAGSENSOR_VORHANDEN` | 0: Condensation sensor not available / coded 1: Condensation sensor available / coded | 1 |
| `0xD96F` | 2E;22 | `FRONTSCHEIBENHEIZUNG` | Windshield heating | 3 |
| `0xD977` | 22 | `KLIMA_TEMPERATUR_SOLLWERT` | Output of the setpoint temperature (left and right) of the air conditioning system. | 2 |
| `0xD978` | 2E | `STEUERN_EINZELADRESSIERUNG` | Address assignment to individual motors. | 5 |
| `0xD97B` | 22 | `KLIMA_LIN_1_ADRESSEN` | Reading of all addressable LIN addresses of the LIN bus system. | 18 |
| `0xD97C` | 2F | `STEUERN_RESET_LIN` | Resetting the LIN bus with switching off the LIN supply voltage. | 0 |
| `0xD980` | 22 | `KLAPPEN_VERSTELLBEREICH` | Reading out the adjustment range of the individual flaps as increments that could be determined via the calibration run. | 20 |
| `0xD981` | 2F | `STEUERN_AUTOADR_KLAPPENMOTOREN` | Starts the auto addressing to assign the motor addresses in the system based on the sequence of the connections on the wiring harness. | 0 |
| `0xD988` | 22 | `KLIMA_TEMPERATUR_MITTE_SOLLWERT` | Output of the set target temperature | 1 |
| `0xD98A` | 22 | `KLP_POS_MISCHLUFT_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD98B` | 22 | `KLP_POS_ZENTRALANTRIEB_WERT` | Reading out the setpoint and actual value of the motor for the central drive with link plate. | 2 |
| `0xD98C` | 22 | `KLP_POS_MISCHLUFT_LINKS_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD98E` | 22 | `KLP_POS_MISCHLUFT_RECHTS_WERT` | Reading out the setpoint and actual value of the flap position of the flap motor. | 2 |
| `0xD98F` | 22 | `MIKROSCHALTER_ZENTRALANTRIEB` | Output of the status of the microswitch on the central drive: 0 = OFF, 1 = ON | 1 |
| `0xD990` | 22 | `TEMP_BELUEFTUNG_WERT` | Ventilation temperature sensor | 1 |
| `0xD991` | 22 | `TEMP_FUSSRAUM_WERT` | Footwell temperature sensor | 1 |
| `0xD995` | 22 | `VORHANDEN_AUDIOBEDIENTEIL` | 0 = not available 1 = available | 1 |
| `0xD998` | 22 | `POTI_SCHICHTUNG_MITTE_WERT` | Potentiometer stratification ventilation: 0 ... 100% | 1 |
| `0xD99C` | 22 | `MOT_POS_BEL_FUSS_LI_RE_WERT` | Reading out the setpoint and actual values for the central drive for ventilation and footwell. | 4 |
| `0xD9A0` | 22 | `VARIANTE_AUDIOBEDIENTEIL` | For the audio control version, see table TAB_VARIANTE_AUDIOBEDIENTEIL | 1 |
| `0xD9A1` | 22 | `BUS_OUT_KOMPRESSORKUPPLUNG_EIN` | Signal for the request to the compressor clutch 0 = clutch open 1 = clutch closed | 1 |
| `0xD9A4` | 22 | `VORHANDEN_EKMV` | Electric refrigerant compressor: see table TAB_KMV_HYBRID_GENERATION | 1 |
| `0xD9A6` | 2E | `STEUERN_ZENTRALANTRIEB` | Control of central drives | 2 |
| `0xD9A7` | 22;2E | `FREIGABE_KOMPRESSOREINLAUF` | Release for compressor inlet | 2 |
| `0xD9A8` | 22 | `KLIMA_VORN_PRG_HFS` | Functional status of front window heating: 0 = OFF 1 = ON | 1 |
| `0xD9AC` | 22 | `WAERMEPUMPE_SENSOREN` | Heat pump sensors | 7 |
| `0xD9AD` | 22;2E | `WAERMEPUMPE_VENTILE` | Heat pump valves | 14 |
| `0xD9AE` | 22 | `VORHANDEN_EDH` | 0x00 = eDH not available 0x01 = eDH available | 1 |
| `0xD9AF` | 22 | `VORHANDEN_WAERMEPUMPE` | 0x00 = heat pump not available 0x01 = heat pump available | 1 |
| `0xD9B1` | 22 | `VORHANDEN_FSH` | 0x00 = front window heating not available 0x01 = front window heating available | 1 |
| `0xD9DE` | 2E;22 | `WAERMEPUMPE_ZWP` | Additional water pump of the heat pump | 3 |
| `0xD9DF` | 2E | `WAERMEPUMPE_EINZELNE_VENTILE` | Control of individual valves of the heat pump | 2 |
| `0xDAD8` | 22 | `SPANNUNG_KLEMME_30_WERT` | Voltage value on the control unit at terminal 30 (accurate to one decimal place) | 1 |
| `0xDAFD` | 22 | `STATUS_KLEMME_R_EIN` | Status of terminal R in the control unit: 0 = OFF, 1 = ON | 1 |
| `0xDAFE` | 22 | `STATUS_KLEMME_15_EIN` | Status of terminal 15 in the control unit: 0 = OFF; 1 = ON | 1 |
| `0xDB06` | 22 | `STATUS_KLEMME_30B_EIN` | Status of terminal 30B in the control unit: 0 = OFF; 1 = ON | 1 |
| `0xDB10` | 22 | `STATUS_KLEMME_50_EIN` | Status of terminal 50 in the control unit: 0 = OFF; 1 = ON | 1 |
| `0xDFC0` | 22 | `HV_EDH_STECKVERBINDUNG` | Status high-voltage plug connection: See table TAB_HV_STECKVERBINDUNG | 1 |
| `0xDFC1` | 22 | `HV_EKMV_STECKVERBINDUNG` | Status high-voltage plug connection: See table TAB_HV_STECKVERBINDUNG | 1 |
| `0x4001` | 2F | `UWB_CPD_DIAGINFO` | Environmental conditions for HV battery cooling performance | 0 |
| `0x4002` | 22 | `UWB_HKLUSV_DIAGINFO` | Diagnostic status of the heating circuit switching valve. Distinction stuck open / closed. | 10 |
| `0x4010` | 22 | `_ADC_EINGAENGE_WERT` | Return value of ADC converter for all analogue input: STAT_ADC_VERDAMPFER_WERT for TEMP_SENS_VERD | 11 |
| `0x4011` | 22 | `_STAT_STANDHEIZUNG_WERT` | Return the value of the parking heater ECU input: WAKESH | 1 |
| `0x4012` | 22 | `_STANDHEIZUNG_AUSGANG` | Command the ECU output OUTPUT_SH | 3 |
| `0x4018` | 2E | `_VALEO_ENABLE` | Enable all Valeo Diag Write jobs: _STEUERN_xx until reset | 1 |
| `0x4019` | 2E;22 | `_VALEO_PCB_HW_NUMBER` | PCB / Electronic nomenclature index: industrial folder revision | 2 |
| `0x401A` | 2E;22 | `_VALEO_PCB_PRODUCTION_DATA` | Production date | 6 |
| `0x401B` | 2E;22 | `_VALEO_PART_NUMBER` | Valeo part number | 2 |
| `0x401C` | 2E;22 | `_VALEO_PART_NUMBER_INDEX` | Valeo part number index | 2 |
| `0x401D` | 2E;22 | `_VALEO_SERIAL_NUMBER` | serial number of the PCB to be set at 0 at the beginning of each day | 2 |
| `0x401E` | 2E;22 | `_ICT_STEP_COUNTER` | indicates if product passed ICT (In Circuit Tester) and functional tests successfully or not. At the end of ICT, when the product is successfully tested, write 0x01 in the step counter address. At the end of Final Tester, when product is successfully tested, write 0x03 in the step counter address | 2 |
| `0x401F` | 2E | `_HWAP_ID` | 1st byte of HWAP ID | 4 |
| `0x4020` | 22 | `_VALEO_LESEN_SPEICHER` | MEMORY BLOCK | 1 |
| `0x4021` | 2E | `_VALEO_LESEN_SCHREIBEN` | Write EERPOM values at block number | 5 |
| `0x4023` | 2E | `_HWAP_VERSION` | HWAP VERSION | 3 |
| `0x2541` | 22 | `STATUS_CALCVN` | Read out Cal-ID (Calibration-ID) and CVN (Calibration Verification Number). (OBD scopes) Byte layout: 20 bytes long 00-15 = STAT_CALID_WERT 16-19 = STAT_CVN_EINH as Hex unit32 in Intel format *(2012 SGBD only)* | 2 |
| `0xD592` | 22;2E | `FBM_SENS_TASTEN` | FBM sensors *(2012 SGBD only)* | 10 |
| `0xD86F` | 22;2E | `KLIMA_TASTEN_VORN` | Climate control panel buttons *(2012 SGBD only)* | 32 |
| `0xD89D` | 22 | `BUS_OUT_WASSERVENTIL_PWM_WERT` | Bus signal, dual water valve *(2012 SGBD only)* | 2 |
| `0xD8B5` | 22;2E | `AUDIO_TASTEN` | Audio control panel buttons *(2012 SGBD only)* | 8 |
| `0xD8C1` | 22;2E | `LEDS_KLIMA_VORN` | LEDs climate control panel *(2012 SGBD only)* | 20 |
| `0xD8C7` | 2E;22 | `EKMV_AKS_GEN20` | Insulation test eKMV *(2012 SGBD only)* | 2 |
| `0xD900` | 22 | `BUS_OUT_WASSERVENTIL_MONO_PWM_WERT` | PWM value water valve in percent *(2012 SGBD only)* | 1 |
| `0xD918` | 22;2E | `EINLAUFSCHUTZ_KOMPRESSOR` | Output of the run-in protection status for the A/C compressor, or writing of the new status. This status is only reset after the run-in process is fully complete. *(2012 SGBD only)* | 3 |
| `0xD96F` | 22;2E | `FRONTSCHEIBENHEIZUNG` | Windshield heating *(2012 SGBD only)* | 3 |
| `0xD9A7` | 2E;22 | `FREIGABE_KOMPRESSOREINLAUF` | Release for compressor inlet *(2012 SGBD only)* | 2 |
| `0xD9AD` | 2E;22 | `WAERMEPUMPE_VENTILE` | Heat pump valves *(2012 SGBD only)* | 14 |
| `0x4002` | 22 | `_STATUS_AUTOADRESIERUNG_MOTOREN` | Auto-addressing of the LIN motors *(2012 SGBD only)* | 10 |
| `0x4010` | 22 | `_STATUS_ADC_EINGAENGE_WERT` | Return value of ADC converter for all analogue input: STAT_ADC_VERDAMPFER_WERT for TEMP_SENS_VERD *(2012 SGBD only)* | 11 |

## BMW i3 / i3s (I01) — EDME (Vehicle control unit / 12V energy mgmt)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xA1D0` | 31 | `ENTLUEFTUNG_KUEHLSYSTEM` | Ventilation routine for cooling system, only for F56 BEV | 2 |
| `0xADC2` | 31 | `ELUE` | Control of electric fans | 3 |
| `0xADC6` | 31 | `ELUE_ZUSATZLUEFTER` | Control of additional fan | 3 |
| `0xADC7` | 31 | `ELUE_RELAIS` | Control relay for electric fan | 2 |
| `0xADC8` | 31 | `ELUE_ZUSATZLUEFTER_RELAIS` | Control relay of additional fan | 2 |
| `0xADF3` | 31 | `EME_EWAP` | Control of the LIN water pump EME with specification of the speed and control time | 4 |
| `0xADFA` | 31 | `MCAMOS` | Return goods analysis of parts from the factory in series | 0 |
| `0xAE02` | 31 | `12V_NACHLADEHISTORIE_LOESCHEN` | Deleting the history memory for the last 4 charging processes of the 12V battery from the high-voltage battery (ring memory with 4 records each) | 0 |
| `0xAE03` | 31 | `12V_NACHLADEHISTOGRAMM_LOESCHEN` | Deletion of the histogram and counter of all charging processes of the 12V battery from the high-voltage system | 0 |
| `0xDE22` | 22 | `EME_KAELTEMITTEL_ABSPERRVENTIL_ON_OFF` | Status of the refrigerant shut-off valve; 0 = valve closed; 1 = valve open | 1 |
| `0xDE23` | 2E | `EME_KAELTEMITTEL_ABSPERRVENTIL` | Control of the refrigerant shut-off valve | 1 |
| `0xDE9C` | 22 | `PEDALWERTGEBER` | Values from the pedal encoder | 3 |
| `0xDEE1` | 22 | `REX_STATISTIK_BETRIEB` | Reading out the operating statistics from the range extender motor | 6 |
| `0xDEE2` | 22 | `REX_STATISTIK_DREHZAHL` | Reading out speed statistics from the range extender motor | 18 |
| `0xDEE3` | 2E | `REX_STATISTIK_RESET` | Resetting the statistics counters from the range extender motor | 1 |
| `0xDEFC` | 2E | `WARTUNGSLAUF_REX_FAELLIG` | Trigger the REX maintenance run | 1 |
| `0xDEFD` | 22 | `ZYKLISCHES_NACHLADEN_INFO` | Reading out of important parameters of the last 4 processes of the cyclical reloading plus the last parking process. | 51 |
| `0xDEFE` | 22 | `ZYKLISCHES_NACHLADEN_HISTOGRAMM` | Reading out the histograms over the service life up to the start of the cyclical reloading and the loading times of the cyclical reloading processes | 16 |
| `0xDF4E` | 2E | `CBS_NV_RESET` | CBS data in EDME | 1 |
| `0xDF53` | 22 | `REX_STATISTIK_TEMPERATUR` | Temperature statistics from the REX burner | 9 |
| `0xDF54` | 22 | `REX_STATISTIK_KILOMETER_KLASSEN` | Statistics with the number of trips in the respective kilometer classes in REX operation. | 5 |
| `0xDF55` | 22 | `REX_STATISTIK_ZYKLEN` | Driving cycle counter | 2 |
| `0xDF56` | 22 | `REX_STATISTIK_SOC_KILOMETER_KLASSEN` | Number of REX starts after X kilometers with Y SOC at the start of the journey | 32 |
| `0xDF5E` | 22 | `REX_STATISTIK_ZAEHLER` | Query meter statistics from the REX network | 3 |
| `0x1061` | 31 | `STEUERN_INTERLOCK` | LOCKED ECU | 0 |
| `0x409D` | 22 | `12V_NACHLADEHISTORIE` | History with important parameters of the 12V recharge function. Last 4 records | 47 |
| `0x409E` | 22 | `12V_NACHLADEHISTOGRAMM` | Reading out the histograms for the 12V recharge function | 16 |
| `0x4101` | 22 | `STATUS_E_S_KL_15_WUP` | Wakeup Line (E_S_KL15_WUP) | 1 |
| `0x4102` | 22 | `STATUS_E_A_PWG1_RAW` | Pedal position sensor 1 raw | 1 |
| `0x4103` | 22 | `STATUS_E_A_PWG2_RAW` | Pedal position sensor 2 raw | 1 |
| `0x4104` | 22 | `STATUS_E_A_TMEL_RAW` | Engine temperature raw | 1 |
| `0x4105` | 22 | `STATUS_BATTERIE_VOLTAGE_RAUS` | Battery voltage raw | 1 |
| `0x4106` | 22 | `STATUS_A_U_PWG1` | 5 V supply 1 | 1 |
| `0x4107` | 22 | `STATUS_A_U_PWG2` | 5 V supply 2 | 1 |
| `0x4109` | 22 | `STATUS_E_A_MEL` | Voltage Fan 2 raw | 1 |
| `0x410A` | 22 | `STATUS_ECU_MICRO_TEMPERATUR` | Ecu micro temperature | 1 |
| `0x410B` | 22 | `STATUS_E_A_TMEL2_RAW` | E_A_TMEL2 | 1 |
| `0x4114` | 2F | `_STEUERN_E_A_TMEL` | engine temperature | 1 |
| `0x4115` | 2F | `_STEUERN_BATTERY_VOLTAGE_RAW` | Battery Voltage Raw | 1 |
| `0x4116` | 2F | `_STEUERN_A_U_PWG1` | 5 V supply 1 | 1 |
| `0x4117` | 2F | `_STEUERN_A_U_PWG2` | 5 V supply 2 | 1 |
| `0x4119` | 2F | `_STEUERN_VOLTAGE_FAN_2` | Voltage Fan 2 | 1 |
| `0x411A` | 2F | `_STEUERN_ECU_MICRO_TEMPERATUR` | ECU temperature | 1 |
| `0x411B` | 2F | `_STEUERN_TMEL2` | Control motor temperature 2 | 1 |
| `0x4120` | 22 | `STATUS_A_S_ELRLY` | Status Electric Fan Relay | 1 |
| `0x4121` | 22 | `STATUS_A_T_ELUE` | Status Electric Fan Module | 1 |
| `0x4122` | 22 | `STATUS_A_T_EWP` | Water pump | 1 |
| `0x4123` | 22 | `STATUS_A_S_KV1` | Expansion Valve | 1 |
| `0x4124` | 22 | `STATUS_A_S_KV2` | Shutoff valve | 1 |
| `0x4125` | 22 | `STATUS_A_S_MEL` | Fan relay 2 | 1 |
| `0x4140` | 2F | `_STEUERN_A_S_ELRLY` | Status electric fan relay | 1 |
| `0x4141` | 2F | `_STEUERN_A_T_ELUE` | Status Electric Fan Module | 1 |
| `0x4142` | 2F | `_STEUERN_A_T_EWP` | Water pump | 1 |
| `0x4143` | 2F | `STEUERN_A_S_KV1` | Expansion Valve | 1 |
| `0x4144` | 2F | `_STEUERN_A_S_KV2` | Shutoff valve | 1 |
| `0x4145` | 2F | `_STEUERN_A_S_MEL` | Fan relay 2 (A_S_MEL) | 1 |
| `0x4182` | 22 | `STATUS_E_A_PWG1` | Pedal position sensor 1 filtered | 1 |
| `0x4183` | 22 | `STATUS_E_A_PWG2_FILTERED` | Pedal position sensor 2 filtered | 1 |
| `0x4184` | 22 | `STATUS_TEMPERATUR_SENSOR_1` | Temperature value of the first temperature sensor in the engine compartment | 1 |
| `0x4185` | 22 | `STATUS_BATTERY_VOLTAGE_FILTERED` | Battery voltage filtered | 1 |
| `0x418B` | 22 | `STATUS_TEMPERATUR_SENSOR_2` | Temperature value of the second temperature sensor in the engine compartment | 1 |
| `0x60C3` | 2F | `AKKS_INPUTOUTPUTCONTROL` | AKKS control | 1 |
| `0x63F0` | 2E | `_AEP_GRUND_LADEENDE` | Requirement to set the final reason for the end of charging | 1 |
| `0xF000` | 31 | `_AEP_TEST_BATTERY_GUARD` | Request to call Battery Guard | 2 |
| `0xF086` | 31 | `STEUERN_BETRIEBSART_EM1` | Control operating mode E-machine 1 | 3 |
| `0xF087` | 31 | `STEUERN_BETRIEBSART_EM2` | Control operating mode E-machine 2 | 3 |
| `0xF0D5` | 31 | `STEUERN_AKKS` | Controlling the active cooling flap | 6 |
| `0xADFD` | 31 | `12V_NACHLADEHISTORIE_SATZ_LESEN` | Read one record of the 12V top-up charge history *(2012 SGBD only)* | 15 |
| `0xDEA2` | 2E | `12V_NACHLADEHISTORIE` | Read/clear the history memory for the last 4 charging events of the 12V battery from the high-voltage battery (ring buffer of 4 records) *(2012 SGBD only)* | 1 |
| `0xDEAF` | 22;2E | `12V_NACHLADEHISTOGRAMM` | Read/clear histogram and counter of all charging events of the 12V battery from the high-voltage system *(2012 SGBD only)* | 25 |

## BMW i3 REx (I01) — REME (Range-extender generator electronics)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xADF4` | 31 | `EME_AKS_EMK` | Command the electric machine in the AKS: 0 - Control on EME-SW; 1 - AKS E-machine requested | 2 |
| `0xADF7` | 31 | `EME_IGBT_FREILAUF` | Opening the IGBTs to switch the e-machine to high impedance on the AC side | 1 |
| `0xDDF0` | 22 | `EME_TEMP_EMASCHINE` | Read the current temperature value of the e-machine in degrees Celsius | 5 |
| `0xDDF1` | 22 | `EME_SPANNUNG_DC_HV` | DC voltage of the e-machine after rectification by the EME (HV battery side, referred to internal) | 1 |
| `0xDDF3` | 22 | `EME_STROM_EMASCHINE_AC` | HV current of the DC/DC converter and the averaged RMS current of the e-machine | 3 |
| `0xDDF4` | 22 | `EME_STROM_EMASCHINE_DC` | DC current (on the HV side) caused by the EMK | 1 |
| `0xDDF5` | 22 | `EME_POSITIONSGEBER` | Angular position of the e-machines in degrees | 1 |
| `0xDDF7` | 22 | `EME_ELEKTRISCHE_MASCHINE` | Read speed and torque of the e-machine | 3 |
| `0xDDFC` | 22 | `EME_INFO_EMK` | Bit-coded derating information from the e-machine control | 1 |
| `0xDDFE` | 22 | `EME_ANTRIEBSART` | Feedback of the currently active drive mode, e.g. recuperation, boost, etc. | 1 |
| `0xDE2E` | 22 | `EME_SERIENNUMMERN_BOSCH` | Serial, part and revision number of the ECU (Bosch) | 4 |

## BMW i3 REx (I01) — RDME (Range-extender engine DME)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x4004` | 22;2C | `SLS_DIAG` | Secondary air system diagnostic status. | 2 |
| `0x4007` | 22 | `STATUS_DIGITAL_0` | Control loop status bank 1 | 1 |
| `0x4402` | 22;2C | `ITOEL` | Oil temperature | 1 |
| `0x4506` | 22 | `IPNWE` | Intake camshaft sensor position in crankshaft degrees | 1 |
| `0x4600` | 22;2C | `IWDKL` | Throttle valve angle relative to the lower stop | 1 |
| `0x4700` | 22;2C | `ISBV1` | ISBV1 | 1 |
| `0x4807` | 22;2C | `INMOT` | Crankshaft speed | 1 |
| `0x480B` | 22 | `IFPWG` | Driver-demand accelerator pedal in % | 1 |
| `0x4A30` | 22;2C | `ILUZ1` | ILUZ1 | 1 |
| `0x4A35` | 22;2C | `ILUZ2` | ILUZ2 | 1 |
| `0x4A85` | 22;2C | `IMUL1` | IMUL1 | 1 |
| `0x4A87` | 22;2C | `FAC_LAM_COR` | limited lambda controller output plus pre control correction. | 1 |
| `0x4A89` | 22;2C | `FAC_LAM_OUT` | lambda controller output | 1 |
| `0x4A96` | 22;2C | `IANWE` | Intake camshaft adaptation value, bank 1 | 1 |
| `0x5801` | 22;2C | `UIPUMG` | Ambient pressure | 1 |
| `0x5802` | 22;2C | `PWMTEV` | PWM control signal for tank ventilation | 1 |
| `0x5803` | 22;2C | `UILAM1` | Lambda sensor adaptation value | 1 |
| `0x5804` | 22;2C | `UIINT1` | Lambda sensor adaptation value | 1 |
| `0x5805` | 22;2C | `UIUDK1` | Absolute throttle valve position (sensor 1) | 1 |
| `0x5806` | 22;2C | `UIUDK2` | Absolute throttle valve position | 1 |
| `0x5807` | 22;2C | `UIKTFS` | Fuel tank level | 1 |
| `0x5808` | 22;2C | `UIGANG` | Ignition angle | 1 |
| `0x5809` | 22;2C | `UTRMLT` | Secondary fuel trim value (long-term) | 1 |
| `0x580A` | 22;2C | `UTRMST` | Secondary fuel trim value (short-term) | 1 |
| `0x580B` | 22;2C | `UILAG1` | Lambda value | 1 |
| `0x580C` | 22;2C | `UILAGSP1` | Lambda setpoint | 1 |
| `0x580D` | 22;2C | `MOTORLAST` | Relative engine load | 1 |
| `0x580E` | 22;2C | `UIPSAU` | Intake manifold pressure - label MAP_MES_SAE | 1 |
| `0x580F` | 22;2C | `UINMOT` | Engine speed | 1 |
| `0x5810` | 22;2C | `UPWG1` | Accelerator pedal position (sensor 1) | 1 |
| `0x5811` | 22;2C | `UPWG2` | Accelerator pedal position (sensor 2) | 1 |
| `0x5812` | 22;2C | `UKSYS` | Fuel system status | 1 |
| `0x5813` | 22;2C | `MOTORLAUFZEIT` | Elapsed time after engine start | 1 |
| `0x5814` | 22;2C | `UITANS` | Intake air temperature from the HFM (air mass meter) | 1 |
| `0x5815` | 22;2C | `UITSAUM` | Air temperature in the intake manifold | 1 |
| `0x5816` | 22;2C | `UITUMGM` | Ambient air temperature | 1 |
| `0x5817` | 22;2C | `UITUMG` | Ambient air temperature | 1 |
| `0x5818` | 22;2C | `UTCLNT` | Coolant temperature | 1 |
| `0x5819` | 22;2C | `UITKUM` | Coolant temperature in degrees Celsius | 1 |
| `0x581A` | 22;2C | `DK_POSITION` | Relative throttle valve position | 1 |
| `0x581B` | 22;2C | `DK_SOLLWERT` | Throttle valve setpoint | 1 |
| `0x581C` | 22;2C | `IUK87` | Battery voltage | 1 |
| `0x581D` | 22;2C | `UIUSV1` | Probe voltage of the wideband lambda sensor upstream of the catalytic converter (ADC value) | 1 |
| `0x581E` | 22;2C | `UIUSN1` | Voltage lambda sensor downstream of catalytic converter (ADC value) | 1 |
| `0x581F` | 22;2C | `FAHRGESCHWINDIGKEIT` | Vehicle speed | 1 |
| `0x5820` | 22;2C | `UIUTANS` | Voltage (air temperature sensor) | 1 |
| `0x5821` | 22;2C | `UIUTANSST` | Air temperature in the intake manifold at first start (current drive cycle) | 1 |
| `0x5822` | 22;2C | `UIUTUMGST` | Ambient air temperature at start | 1 |
| `0x5823` | 22;2C | `UIUPW1` | Voltage (pedal value sensor 1) | 1 |
| `0x5824` | 22;2C | `UIUPW2` | Voltage (pedal value sensor 2) | 1 |
| `0x5825` | 22;2C | `VP_TCO_ENVD` | Voltage (coolant temperature sensor) | 1 |
| `0x5826` | 22;2C | `TCO_ST_DC` | Coolant temperature at first start (current drive cycle) | 1 |
| `0x5827` | 22;2C | `TCO_STOP` | Coolant temperature when the engine is switched off | 1 |
| `0x5828` | 22;2C | `CL_MMV_ENVD` | Charge in the activated-carbon filter (moving average) | 1 |
| `0x5829` | 22;2C | `MFF_SP_MV_KWP` | Fuel mass setpoint | 1 |
| `0x582A` | 22;2C | `TI_1_HOM_ENVD_1` | Injection time (cylinder-specific, first pulse, cylinder 1) | 1 |
| `0x582B` | 22;2C | `TI_1_HOM_ENVD_2` | Injection time (cylinder-specific, first pulse, cylinder 2) | 1 |
| `0x582C` | 22;2C | `UMAIRT` | Air mass flow per segment | 1 |
| `0x582D` | 22;2C | `UMAIRS` | Air mass flow per segment | 1 |
| `0x582E` | 22;2C | `STAT_0X582E_WERT` | Air mass | 1 |
| `0x582F` | 22;2C | `STAT_0X582F_WERT` | Pressure regulator actuation value (divided by ambient pressure) | 1 |
| `0x5830` | 22;2C | `FAC_AD_KNK` | Knock factor | 1 |
| `0x5831` | 22;2C | `V_TPS_1` | Voltage (throttle valve position sensor 1) | 1 |
| `0x5832` | 22;2C | `V_TPS_2` | Voltage (throttle valve position sensor 2) | 1 |
| `0x5833` | 22;2C | `ENVD_0_MON` | Environment data for general error | 1 |
| `0x5834` | 22;2C | `ENVD_1_MON` | Environment data for general error | 1 |
| `0x5835` | 22;2C | `ENVD_2_MON` | Environment data for general error | 1 |
| `0x5836` | 22;2C | `ENVD_3_MON` | Environment data for general error | 1 |
| `0x5837` | 22;2C | `ENVD_0_MON_3` | Environment data for processor error | 1 |
| `0x5838` | 22;2C | `ENVD_1_MON_3` | Environment data for processor error | 1 |
| `0x5839` | 22;2C | `ENVD_2_MON_3` | Environment data for processor error | 1 |
| `0x583A` | 22;2C | `ENVD_3_MON_3` | Environment data for processor error | 1 |
| `0x5A0E` | 22 | `IUSGI` | ECU temperature | 1 |
| `0x602A` | 2F | `STEUERN_DK` | Actuate throttle valve | 3 |
| `0x60CB` | 2F | `STEUERN_SLP` | Control secondary air pump. | 3 |
| `0x60CF` | 2F | `STEUERN_TEV` | Tank ventilation valve | 3 |
| `0x60D8` | 2F | `STEUERN_EKP` | Actuate electric fuel pump | 3 |
| `0xF020` | 31 | `SLSCHECK` | Secondary air system self-check | 1 |
| `0xF022` | 31 | `TEVCHECK` | Tank ventilation valve self-check | 1 |
| `0xF030` | 31 | `ADAP_SELEKTIV_LOESCHEN` | Clear adaptations | 6 |
| `0xF031` | 31 | `ADAP2_SELEKTIV_LOESCHEN` | Clear adaptations (2) | 6 |
| `0xF043` | 31 | `MONTAGEMODUS` | Activate assembly mode | 2 |
| `0xF0F2` | 31 | `RAM` | Save RAM / RAM save status | 1 |

## BMW i8 (I12) — EME (Front e-machine electronics)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xADC0` | 31 | `STEUERN_START_LADEN` | Request charging start | 1 |
| `0xADC1` | 31 | `STEUERN_STOP_LADEN` | Request charging stop | 1 |
| `0xADC4` | 31 | `REX_ON_OFF` | Switching on / off the range extender combustion engine | 1 |
| `0xADC9` | 31 | `AE_EWP` | Actuate and read out the electric coolant pump (actuation possible only when AE temperature is below threshold, house keeping not active, EWP not switched off, and manual speed control deactivated) | 5 |
| `0xADF1` | 31 | `EME_DCDC_WANDLER` | Control or read the status of the DC / DC converter | 8 |
| `0xADF4` | 31 | `EME_AKS_EMK` | Command the electric machine in the AKS: 0 - Control on EME-SW; 1 - AKS E-machine requested | 2 |
| `0xADF6` | 31 | `AE_ROTORLAGESENSOR_ANLERNEN` | Teaching in the rotor position sensor (TA-EOL STEUERN) | 6 |
| `0xADF8` | 31 | `AE_KLASSIERUNG` | Reading out the speed / torque classification data | 44 |
| `0xADF9` | 31 | `AE_DCDC_HISTOGRAMM` | Reading the requested histogram of the DCDC converter | 11 |
| `0xDDF6` | 22 | `EME_DCDC_LV` | Voltage / current DCDC (12V vehicle electrical system) at the B + bolt | 2 |
| `0xDE00` | 22 | `EME_HVPM_DCDC_ANSTEUERUNG` | Return values from the HVPM for DCDC control | 16 |
| `0xDE02` | 22 | `EME_HVPM_HV_SYSTEM_ON_OFF` | High-voltage system on / off | 7 |
| `0xDE03` | 22 | `EME_HVPM_ENERGIEBORDNETZ` | Return values of the HVPM for HV energy and cell voltages | 34 |
| `0xDE04` | 22 | `EME_HVPM_ENERGIEBORDNETZ_2` | Number of times the vehicle was ready to drive in the SOC area | 14 |
| `0xDE06` | 22 | `EME_HVPM_PKOR` | HVPM performance coordinator | 24 |
| `0xDE08` | 2E | `EME_HVPM_INFOSPEICHER_PKOR_LOESCHEN` | All fault memory entries of diagnostic job STATUS_HVPM_EKMV are set to zero. | 1 |
| `0xDE09` | 2E | `EME_HVPM_INFOSPEICHER_STRZLR_LOESCHEN` | Clear the info memory HSPM (STRZL) | 1 |
| `0xDE0A` | 2E | `EME_HVPM_INFOSPEICHER_SPMON_LOESCHEN` | Deleting the information memory HVPMP (SPMON) | 1 |
| `0xDE0C` | 22 | `EME_HVIL_GESAMT` | Reading out the HVIL status in the EME; if HVIL is interrupted, then not ok | 1 |
| `0xDE18` | 22 | `EME_HVPM_SPANNUNGSFREIHEIT` | Info memory for the de-energized state of the high-voltage system (monitored by HVPM) | 40 |
| `0xDE19` | 22 | `EME_ELUP` | Number of brake actuations, running time and starts of the ELUP | 3 |
| `0xDE1C` | 22 | `EME_HVPM_DCDC_ALS` | HVPM DCDC ALS | 4 |
| `0xDE2D` | 22 | `AE_CPLD_VERSION` | CPLD version | 1 |
| `0xDE71` | 22 | `AE_CHARGE_ENABLE` | Statement about the granting of loading clearance | 1 |
| `0xDE75` | 22 | `AE_HV_SPANNUNG_LESEN` | Values of all intermediate circuit voltages | 5 |
| `0xDE7D` | 22 | `AE_ROHSIG_AUSGANG` | Raw signals output pins | 4 |
| `0xDE7E` | 22 | `AE_ROHSIG_EINGANG_SENS_ELUP_BUDS` | Raw signals output pins sensors ELUP, BUDS | 2 |
| `0xDE7F` | 22 | `AE_ROHSIG_EINGANG_SENS_EM_INV` | Raw signals sensors / inputs for e-machines / converters | 13 |
| `0xDE80` | 22 | `AE_ROHSIG_EINGANG_SENS_PARKSPERRE` | Raw signals sensors / inputs parking lock | 3 |
| `0xDE81` | 22 | `AE_ROHSIG_EINGANG_SENS_SG` | Raw signals sensors / inputs control unit | 5 |
| `0xDE82` | 22 | `AE_ROHSIG_EINGANG_SENS_SLE` | Raw signals sensors / inputs SLE | 10 |
| `0xDE83` | 22 | `AE_ROHSIG_EINGANG_SENS_DCDC` | Raw signals sensors / inputs DC / DC converter | 3 |
| `0xDE84` | 22 | `AE_BETRIEBSZUSTAND_SLE` | Operating modes SLE | 6 |
| `0xDE85` | 22 | `AE_SLE_LEISTUNG` | Power values intermediate circuit of the SLE | 3 |
| `0xDE86` | 22 | `AE_SLE_SPANNUNG` | AC and DC voltages SLE | 3 |
| `0xDE87` | 22 | `AE_SLE_STROM` | AC and DC currents SLE | 4 |
| `0xDE88` | 22 | `AE_SPANNUNG_KLEMME30B` | current voltage at KL30B | 1 |
| `0xDE89` | 22 | `AE_STROM_DCDC` | DC / DC converter currents | 6 |
| `0xDE8B` | 2E;22 | `AE_STROM_MAX` | Maximum measured currents since last reset or reset of values | 9 |
| `0xDE8C` | 22 | `AE_TEMP_LE` | Temperatures control unit drive electronics | 21 |
| `0xDE92` | 22 | `AE_ZUSTAND_1_DCDC` | DC / DC converter status | 3 |
| `0xDE93` | 2E;22 | `AE_ELUP` | Current status ELUP or activate / deactivate ELUP | 5 |
| `0xDE96` | 22 | `AE_ZUSTAND_DCDC_FEHLERBILD` | Return of active / inactive errors DC / DC converter | 1 |
| `0xDE9E` | 22 | `STATUS_CONNECTED_DRIVE` | Information about Connected Drive | 10 |
| `0xDEA0` | 22 | `STATUS_TSR_LADEN` | All return values regarding TSR charging | 130 |
| `0xDEA5` | 22 | `AE_BUDS` | Brake vacuum sensor value | 1 |
| `0xDEA6` | 22 | `AE_TEMP_EMASCHINE` | Value of the current temperatures of the e-machine in degrees Celsius | 2 |
| `0xDEA7` | 22 | `AE_ELEKTRISCHE_MASCHINE` | Reading out the speed, torque and operating mode of the electric machine | 4 |
| `0xDEA9` | 22 | `AE_ZUSTAND_2_DCDC` | Various statuses returned from the DCDC converter | 1 |
| `0xDEB1` | 2E | `AE_ROTORLAGESENSOR_SCHREIBEN` | Direct write of the resolver offset angle | 1 |
| `0xDEB2` | 2E | `AE_DCDC_TEMPHISTOGRAMM_LESEN` | Read out temperature histograms DCDC / reset temperature histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB3` | 2E | `AE_DCDC_LEISTUNGSHISTOGRAMM` | Read out power histograms DCDC converter / reset power histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB4` | 2E | `AE_RESET_TEMP_MIN_MAX` | Resetting the minimum and maximum temperature of the DC / DC converter (0 = no reset; 1 = reset) | 1 |
| `0xDEB5` | 22 | `AE_PIC_SW_VERSION` | Returns current version of the PIC software | 2 |
| `0xDEB6` | 2E | `AE_ROTORLAGESENSOR_RESET` | Resetting the resolver offset angle | 1 |
| `0xDEB7` | 2E | `AE_KLASSIERUNG_LOESCHEN` | Deletion of the entire classification data | 1 |
| `0xDEBC` | 22 | `AE_CTRL_VERSION` | Controller board version | 1 |
| `0xDEBD` | 22 | `AE_SPANNUNG_DCDC` | Voltages DCDC converter | 2 |
| `0xDEBE` | 22 | `AE_SPANNUNG_LE` | Internal voltages of the power electronics | 9 |
| `0xDEBF` | 22 | `AE_SYSSTATE` | Internal status states of the control unit | 4 |
| `0xDEC4` | 22;2E | `AE_PRND_AKTOR_EINLERNEN` | Read the learning status of the PRND actuator, or initialize the PRND actuator | 3 |
| `0xDEC5` | 22 | `AE_PRND_AKTOR_POSITION` | Current position of the PRND actuator | 1 |
| `0xDEC6` | 22 | `AE_PRND_AKTOR_POSITIONEN` | Read the learned PRND actuator positions | 4 |
| `0xDEC7` | 22 | `AE_PRND_AKTOR_SENSOREN` | Status of the PRND actuator sensors | 2 |
| `0xDEC8` | 22 | `AE_PRND_AKTOR_SPANNUNGEN` | Read the voltages of the PRND actuator | 2 |
| `0xDEC9` | 22 | `AE_PRND_AKTOR_SW` | PRND actuator software status | 1 |
| `0xDECA` | 22 | `AE_PRND_AKTOR_VERSION` | Read current version of the PRND actuator software | 2 |
| `0xDECB` | 2E | `AE_PRND_AKTOR` | Initiates the approach to the transmission positions P/R/N/D | 1 |
| `0xDECC` | 2E | `AE_PRND_AKTOR_AUSLIEFERPOSITION` | Moves the actuator to the delivery position (based on default data, also possible in the non-learned state). The actuator can then be learned | 1 |
| `0xDECD` | 2E | `AE_PRND_AKTOR_MAGNET` | Switch on the solenoid for the PRND actuator | 1 |
| `0xDECE` | 2E | `AE_PRND_AKTOR_NVRAM_LOESCHEN` | Clears the NV-RAM data of the PRND actuator. Important: after this job the ECU must go to sleep so that the cleared values are adopted in NV-RAM | 1 |
| `0xDEDD` | 22 | `AE_FAHRSTUFE` | current actual position of the drive train (PRND) | 1 |
| `0xDEDE` | 22 | `AE_LSC_LADEN` | Feedback on the charging process | 26 |
| `0x400C` | 2E | `AE_SN_SETZEN` | serial number | 4 |
| `0x400D` | 2E | `AE_HWCAL_SETZEN` | Set hardware calibration data of the AE The serial number cannot be set (own job _steuern_sn_etzen) !!! | 5 |
| `0x400E` | 2E | `AE_HWCAL_FLASHEN` | Writes the HWCALs of a certain block into the flash | 2 |
| `0x400F` | 2E | `AE_HWCAL_MODE` | Bring the SG into HWCAL Flash mode | 1 |
| `0xF010` | 31 | `AE_HWCAL_LESEN` | Reading out the HWCALs using the block number and processor | 5 |
| `0xF011` | 31 | `AE_RESETINFO_LESEN` | Reading out the reset info from the flash | 13 |
| `0xF050` | 31 | `AE_FREILAUF_MODUS` | Free running mode | 1 |

## BMW i8 (I12) — REME (High-voltage starter-generator electronics)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xADF4` | 31 | `EME_AKS_EMK` | Command the electric machine in the AKS: 0 - Control on EME-SW; 1 - AKS E-machine requested | 2 |
| `0xADF7` | 31 | `EME_IGBT_FREILAUF` | Opening the IGBTs to switch the e-machine to high impedance on the AC side | 1 |
| `0xDDF0` | 22 | `EME_TEMP_EMASCHINE` | Read the current temperature value of the e-machine in degrees Celsius | 5 |
| `0xDDF1` | 22 | `EME_SPANNUNG_DC_HV` | DC voltage of the e-machine after rectification by the EME (HV battery side, referred to internal) | 1 |
| `0xDDF3` | 22 | `EME_STROM_EMASCHINE_AC` | HV current of the DC/DC converter and the averaged RMS current of the e-machine | 3 |
| `0xDDF4` | 22 | `EME_STROM_EMASCHINE_DC` | DC current (on the HV side) caused by the EMK | 1 |
| `0xDDF5` | 22 | `EME_POSITIONSGEBER` | Angular position of the e-machines in degrees | 1 |
| `0xDDF7` | 22 | `EME_ELEKTRISCHE_MASCHINE` | Read speed and torque of the e-machine | 3 |
| `0xDDFC` | 22 | `EME_INFO_EMK` | Bit-coded derating information from the e-machine control | 1 |
| `0xDDFE` | 22 | `EME_ANTRIEBSART` | Feedback of the currently active drive mode, e.g. recuperation, boost, etc. | 1 |
| `0xDE2E` | 22 | `EME_SERIENNUMMERN_BOSCH` | Serial, part and revision number of the ECU (Bosch) | 4 |

## BMW 530Le (F18) — SME (HV battery management)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xAD61` | 31 | `ISOLATION` | Isolation test result | 2 |
| `0xAD69` | 31 | `NV_DATEN_SCHREIBEN` | Saving data in the NV-RAM | 1 |
| `0xAD6B` | 31 | `SYMMETRIERUNG` | Activate balancing | 1 |
| `0xAD6E` | 31 | `ZELLSPANNUNG_LESEN` | Cell whose voltage is to be determined | 2 |
| `0xAD7B` | 31 | `ENTLUEFTUNG_KUEHLKREIS` | Routine for venting the coolant circuit (dedicated cooling for HV battery) | 1 |
| `0xDD60` | 22 | `SCHUETZ_SCHALTER` | Job: Status, contactor switch: closed or open Result: Status of the contactor switch: closed or open. See table TAB_SCHUETZ_SCHALTER for results | 1 |
| `0xDD61` | 22;2E | `SCHUETZ_FREIGABE` | Writes or reads the bit to enable or disable the contactor switch. Job is clamp-safe | 2 |
| `0xDD64` | 22 | `HVIL` | Job: Result of HVIL test Result: Result of HVIL test | 1 |
| `0xDD66` | 22 | `HV_SPANNUNG` | Job: HV voltage of the DC link before the contactors Result: DC-link voltage before the contactors, independent of contactor state | 1 |
| `0xDD67` | 22 | `ANZAHL_KUEHLANFORDERUNG_DRINGEND` | Job: Counter describes how often a higher temperature state was reached in consecutive terminal cycles. (Maximum value) Result: Number of higher temperature states in consecutive terminal cycles. | 1 |
| `0xDD69` | 22 | `HV_STROM` | Job: HV current Result: HV current in A | 1 |
| `0xDD6A` | 22 | `ISOLATIONSWIDERSTAND` | Reading out the currently applied insulation resistance | 4 |
| `0xDD6C` | 22 | `KUEHLKREISLAUF_TEMP` | Job: Temperature of the coolant circuit Result: Temperature of the coolant medium in °C | 1 |
| `0xDD6F` | 22;2E | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: Closed or open / close or open | 2 |
| `0xDD73` | 22 | `CUMULATIVE_LADUNG` | Job: Status, cumulative charge Result: The cumulative charge for charging events in Ah | 1 |
| `0xDD74` | 22 | `CUMULATIVE_ENTLADUNG` | Job: Status, cumulative discharge Result: The cumulative charge for discharge events in Ah | 1 |
| `0xDD76` | 22 | `STATUS_KL30C_SPANNUNG` | Job: Voltage, terminal 30C Result: Voltage, terminal 30C in V | 1 |
| `0xDD7D` | 22 | `STROMGRENZEN` | Current limits | 2 |
| `0xDD7E` | 22 | `SPANNUNGSGRENZEN` | Voltage limits | 2 |
| `0xDD91` | 22 | `ZEIT_SOC_KLASSE` | Time since installation in SOC classes | 12 |
| `0xDDA1` | 2E;22 | `KUEHLMITTELPUMPE` | Result values or control of the coolant pump for cooling the HV battery in % (0-100%) | 3 |
| `0xDDB4` | 22 | `HV_SPANNUNG_BATTERIE` | Job: Battery voltage behind the contactors, independent of contactor state Result: Battery voltage behind the contactors, independent of contactor state | 1 |
| `0xDDB6` | 22 | `ALTERUNG_INNENWIDERSTAND` | Job: Internal resistance aging in percent: internal resistance of the storage (battery) in new condition relative to the current internal resistance value  (R_neu /R_akt) *100   (100% = new condition, decreases with aging) Result: Internal resistance aging in percent: internal resistance of the storage (battery) in new condition relative to the current internal resistance value  (R_neu /R_akt) *100   (100% = new condition, decreases with aging) | 1 |
| `0xDDB7` | 22 | `REFERENZ_KAPAZITAET` | Job: Remaining capacity of the storage (battery), percentage value: ( C_akt/C_nenn(neu) ) * 100, 100 = new condition. Raw estimate from the onboard capacity estimator of the overall storage Result: Remaining capacity of the storage (battery), percentage value: ( C_akt/C_nenn(neu) ) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDBC` | 22 | `ANZEIGE_SOC` | current advertisement Soc | 3 |
| `0xDDBD` | 22 | `SERVICE_DISCONNECT` | Job: Status of the service disconnect (0 = open, 1 = closed) Result: Status, service disconnect (0 = open, 1 = closed) | 1 |
| `0xDDBE` | 22 | `VORLADUNG` | Info about time, current and temperatures during pre-charging | 15 |
| `0xDDBF` | 22 | `ZELLSPANNUNGEN_MIN_MAX` | minimum and maximum single cell voltages are output | 2 |
| `0xDDC0` | 22 | `TEMPERATUREN` | Output of minimum measured temperature, maximum measured temperature, average measured temperature, maximum cell core temperature | 4 |
| `0xDDC4` | 2E;22 | `SOC` | Read out SOC value (in%) and plausibility or specification of the SOC value (0-100%) | 4 |
| `0xDDCA` | 22 | `SERIENNUMMER_ECU` | Job: Serial number, SME ECU Result: Serial number of the SME ECU | 1 |
| `0xDDCB` | 22 | `SOC_GRENZEN` | Reading and changing the SOC limits | 2 |
| `0xDDCD` | 2E | `CC_MELDUNG` | Activation / deactivation of the sending of CC messages (0 = sending not active; 1 = sending active) | 1 |
| `0xDF61` | 2E | `SOC_GRENZE_OBEN` | Opening/resetting the upper SOC limit | 2 |
| `0xDF71` | 22 | `PROJEKT_PARAMETER` | Reading out the project-specific parameters | 4 |
| `0xDF7B` | 2E | `RESET_ISOLATIONSMESSWERTE` | Resetting the insulation resistance readings | 2 |
| `0x5000` | 2F | `STEUERN_KUEHLKREISLAUF_VENTIL` | Control coolant valve: close or open | 1 |
| `0x5001` | 2F | `STEUERN_KUEHLMITTELPUMPE` | Control of the coolant pump for cooling the HV battery in % (0-100%) | 2 |
| `0x6509` | 2E | `_SERIENNUMMER` | HV battery (storage) serial number | 2 |
| `0x6512` | 2E | `_MESSBOTSCHAFTEN` | Switch measurement messages on / off | 2 |

## BMW 530Le (F18) — EME (E-machine electronics)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xADC0` | 31 | `STEUERN_START_LADEN` | Request charging start | 1 |
| `0xADC1` | 31 | `STEUERN_STOP_LADEN` | Request charging stop | 1 |
| `0xADC4` | 31 | `REX_ON_OFF` | Switching on / off the range extender combustion engine | 1 |
| `0xADC9` | 31 | `AE_EWP` | Actuate and read out the electric coolant pump (actuation possible only when AE temperature is below threshold, house keeping not active, EWP not switched off, and manual speed control deactivated) | 5 |
| `0xADF1` | 31 | `EME_DCDC_WANDLER` | Control or read the status of the DC / DC converter | 8 |
| `0xADF4` | 31 | `EME_AKS_EMK` | Command the electric machine in the AKS: 0 - Control on EME-SW; 1 - AKS E-machine requested | 2 |
| `0xADF6` | 31 | `AE_ROTORLAGESENSOR_ANLERNEN` | Teaching in the rotor position sensor (TA-EOL STEUERN) | 6 |
| `0xADF8` | 31 | `AE_KLASSIERUNG` | Reading out the speed / torque classification data | 44 |
| `0xADF9` | 31 | `AE_DCDC_HISTOGRAMM` | Reading the requested histogram of the DCDC converter | 11 |
| `0xDDF6` | 22 | `EME_DCDC_LV` | Voltage / current DCDC (12V vehicle electrical system) at the B + bolt | 2 |
| `0xDE00` | 22 | `EME_HVPM_DCDC_ANSTEUERUNG` | Return values from the HVPM for DCDC control | 16 |
| `0xDE02` | 22 | `EME_HVPM_HV_SYSTEM_ON_OFF` | High-voltage system on / off | 7 |
| `0xDE03` | 22 | `EME_HVPM_ENERGIEBORDNETZ` | Return values of the HVPM for HV energy and cell voltages | 34 |
| `0xDE04` | 22 | `EME_HVPM_ENERGIEBORDNETZ_2` | Number of times the vehicle was ready to drive in the SOC area | 14 |
| `0xDE06` | 22 | `EME_HVPM_PKOR` | HVPM performance coordinator | 24 |
| `0xDE08` | 2E | `EME_HVPM_INFOSPEICHER_PKOR_LOESCHEN` | All fault memory entries of diagnostic job STATUS_HVPM_EKMV are set to zero. | 1 |
| `0xDE09` | 2E | `EME_HVPM_INFOSPEICHER_STRZLR_LOESCHEN` | Clear the info memory HSPM (STRZL) | 1 |
| `0xDE0A` | 2E | `EME_HVPM_INFOSPEICHER_SPMON_LOESCHEN` | Deleting the information memory HVPMP (SPMON) | 1 |
| `0xDE0C` | 22 | `EME_HVIL_GESAMT` | Reading out the HVIL status in the EME; if HVIL is interrupted, then not ok | 1 |
| `0xDE18` | 22 | `EME_HVPM_SPANNUNGSFREIHEIT` | Info memory for the de-energized state of the high-voltage system (monitored by HVPM) | 40 |
| `0xDE19` | 22 | `EME_ELUP` | Number of brake actuations, running time and starts of the ELUP | 3 |
| `0xDE1C` | 22 | `EME_HVPM_DCDC_ALS` | HVPM DCDC ALS | 4 |
| `0xDE2D` | 22 | `AE_CPLD_VERSION` | CPLD version | 1 |
| `0xDE70` | 22 | `AE_AKS_EMK` | Status of the AKS at the e-machine | 1 |
| `0xDE71` | 22 | `AE_CHARGE_ENABLE` | Statement about the granting of loading clearance | 1 |
| `0xDE75` | 22 | `AE_HV_SPANNUNG_LESEN` | Values of all intermediate circuit voltages | 5 |
| `0xDE7E` | 22 | `AE_ROHSIG_EINGANG_SENS_ELUP_BUDS` | Raw signals output pins sensors ELUP, BUDS | 2 |
| `0xDE7F` | 22 | `AE_ROHSIG_EINGANG_SENS_EM_INV` | Raw signals sensors / inputs for e-machines / converters | 13 |
| `0xDE81` | 22 | `AE_ROHSIG_EINGANG_SENS_SG` | Raw signals sensors / inputs control unit | 5 |
| `0xDE82` | 22 | `AE_ROHSIG_EINGANG_SENS_SLE` | Raw signals sensors / inputs SLE | 10 |
| `0xDE83` | 22 | `AE_ROHSIG_EINGANG_SENS_DCDC` | Raw signals sensors / inputs DC / DC converter | 3 |
| `0xDE84` | 22 | `AE_BETRIEBSZUSTAND_SLE` | Operating modes SLE | 6 |
| `0xDE85` | 22 | `AE_SLE_LEISTUNG` | Power values intermediate circuit of the SLE | 3 |
| `0xDE86` | 22 | `AE_SLE_SPANNUNG` | AC and DC voltages SLE | 3 |
| `0xDE87` | 22 | `AE_SLE_STROM` | AC and DC currents SLE | 4 |
| `0xDE88` | 22 | `AE_SPANNUNG_KLEMME30B` | current voltage at KL30B | 1 |
| `0xDE89` | 22 | `AE_STROM_DCDC` | DC / DC converter currents | 6 |
| `0xDE8B` | 2E;22 | `AE_STROM_MAX` | Maximum measured currents since last reset or reset of values | 9 |
| `0xDE8C` | 22 | `AE_TEMP_LE` | Temperatures control unit drive electronics | 21 |
| `0xDE92` | 22 | `AE_ZUSTAND_1_DCDC` | DC / DC converter status | 3 |
| `0xDE93` | 22;2E | `AE_ELUP` | Current status ELUP or activate / deactivate ELUP | 5 |
| `0xDE96` | 22 | `AE_ZUSTAND_DCDC_FEHLERBILD` | Return of active / inactive errors DC / DC converter | 1 |
| `0xDE9E` | 22 | `STATUS_CONNECTED_DRIVE` | Information about Connected Drive | 10 |
| `0xDEA0` | 22 | `STATUS_TSR_LADEN` | All return values regarding TSR charging | 130 |
| `0xDEA5` | 22 | `AE_BUDS` | Brake vacuum sensor value | 1 |
| `0xDEA6` | 22 | `AE_TEMP_EMASCHINE` | Value of the current temperatures of the e-machine in degrees Celsius | 2 |
| `0xDEA7` | 22 | `AE_ELEKTRISCHE_MASCHINE` | Reading out the speed, torque and operating mode of the electric machine | 4 |
| `0xDEA9` | 22 | `AE_ZUSTAND_2_DCDC` | Various statuses returned from the DCDC converter | 1 |
| `0xDEB1` | 2E | `AE_ROTORLAGESENSOR_SCHREIBEN` | Direct write of the resolver offset angle | 1 |
| `0xDEB2` | 2E | `AE_DCDC_TEMPHISTOGRAMM_LESEN` | Read out temperature histograms DCDC / reset temperature histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB3` | 2E | `AE_DCDC_LEISTUNGSHISTOGRAMM` | Read out power histograms DCDC converter / reset power histograms (0 = no reset; 1 = reset) | 1 |
| `0xDEB4` | 2E | `AE_RESET_TEMP_MIN_MAX` | Resetting the minimum and maximum temperature of the DC / DC converter (0 = no reset; 1 = reset) | 1 |
| `0xDEB5` | 22 | `AE_PIC_SW_VERSION` | Returns current version of the PIC software | 2 |
| `0xDEB6` | 2E | `AE_ROTORLAGESENSOR_RESET` | Resetting the resolver offset angle | 1 |
| `0xDEB7` | 2E | `AE_KLASSIERUNG_LOESCHEN` | Deletion of the entire classification data | 1 |
| `0xDEBC` | 22 | `AE_CTRL_VERSION` | Controller board version | 1 |
| `0xDEBD` | 22 | `AE_SPANNUNG_DCDC` | Voltages DCDC converter | 2 |
| `0xDEBE` | 22 | `AE_SPANNUNG_LE` | Internal voltages of the power electronics | 9 |
| `0xDEBF` | 22 | `AE_SYSSTATE` | Internal status states of the control unit | 4 |
| `0xDEDE` | 22 | `AE_LSC_LADEN` | Feedback on the charging process | 26 |
| `0x400C` | 2E | `AE_SN_SETZEN` | serial number | 4 |
| `0x400D` | 2E | `AE_HWCAL_SETZEN` | Set hardware calibration data of the AE The serial number cannot be set (own job _steuern_sn_etzen) !!! | 5 |
| `0x400E` | 2E | `AE_HWCAL_FLASHEN` | Writes the HWCALs of a certain block into the flash | 2 |
| `0x400F` | 2E | `AE_HWCAL_MODE` | Bring the SG into HWCAL Flash mode | 1 |
| `0xF010` | 31 | `AE_HWCAL_LESEN` | Reading out the HWCALs using the block number and processor | 5 |
| `0xF011` | 31 | `AE_RESETINFO_LESEN` | Reading out the reset info from the flash | 13 |
| `0xF050` | 31 | `AE_FREILAUF_MODUS` | Free running mode | 1 |

## BMW X5 xDrive40e (F15) — SLE (Charging electronics incl. LIM)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xAF40` | 31 | `BETRIEBSART` | Change operating mode of charging electronics | 3 |
| `0xAF41` | 31 | `SLE_TEMPHISTOGRAMM_LESEN` | Read the SLE temperature histograms | 8 |
| `0xDEF0` | 2E;22 | `ZV_LADESTECKER` | Status and control of charging plug (depending on plug type and market) 0 = unlocked, 1 = locked | 3 |
| `0xDEF1` | 22;2E | `ZV_LADEKLAPPE` | Status or control loading flap (0 = unlocked, 1 = locked) | 3 |
| `0xDEF2` | 22 | `LADEBEREITSCHAFT_LIM` | Ready to charge (HW line), (1 = yes, 0 = no) sent from LIM to SLE | 1 |
| `0xDEF3` | 22;2E | `LED_LADESTATUS` | Status or control LED for charging status (RGB light ring) | 2 |
| `0xDEF4` | 2E;22 | `LED_SUCHBELEUCHTUNG` | Status or activation of the LED for search lighting (0 = not activated, 1 = activated) - only for separate DC charging socket | 2 |
| `0xDEF5` | 22 | `PROXIMITY` | Current status of the proximity | 2 |
| `0xDEF6` | 22 | `PILOTSIGNAL` | current data of the pilot signal about the charging current | 6 |
| `0xDF20` | 22 | `BETRIEBSART_AKTUELL` | Status of the current operating mode of the charger electronics | 1 |
| `0xDF21` | 22 | `FEHLERZUSTAENDE` | Fault states of the charging electronics | 3 |
| `0xDF23` | 22 | `WIRKUNGSGRAD` | Efficiency status | 1 |
| `0xDF24` | 22 | `WIRKUNGSGRAD_LADEZYKLUS` | Charge cycle efficiency status | 1 |
| `0xDF25` | 22 | `AC_PHASENANZAHL` | Status of the number of AC phases | 1 |
| `0xDF26` | 22 | `NETZFREQUENZ` | Mains frequency status per phase | 1 |
| `0xDF27` | 22 | `LADEDAUER` | Charge duration status | 1 |
| `0xDF28` | 22 | `TEMPERATUR_LADEELEKTRONIK` | Current temperature of charging electronics | 1 |
| `0xDF29` | 22 | `SME_BEGRENZUNGSGROESSEN` | Charging power limitation values from SME | 2 |
| `0xDF2E` | 22 | `HVDC_LEISTUNG` | Status HV DC power of the charger electronics | 1 |
| `0xDF2F` | 22 | `HVDC_LEISTUNG_MAX` | Status maximum HV DC power of the charger electronics | 1 |
| `0xDF30` | 22 | `AC_WIRKLEISTUNG_LADEZYKLUS` | Status of active power drawn from the mains, current charge cycle | 1 |
| `0xDF31` | 22 | `AC_SPANNUNG_EFFEKTIV` | Status RMS values of the AC phase voltages per phase | 1 |
| `0xDF32` | 22 | `HVDC_SPANNUNG` | HV DC voltage at the charging electronics | 1 |
| `0xDF33` | 22 | `HVDC_SPANNUNG_MAX` | Maximum HV DC voltage at the charging electronics | 1 |
| `0xDF34` | 22 | `HVDC_STROM` | Status HV DC current of the charger electronics | 1 |
| `0xDF35` | 22 | `HVDC_STROM_MAX` | Status maximum HV DC current of the charger electronics | 1 |
| `0xDF36` | 22 | `AC_STROM_EFFEKTIV_LEITER` | Status RMS values of the AC phase currents per phase | 1 |
| `0xDF37` | 22 | `AC_STROM_MAX` | Status maximum AC current of the charger electronics | 1 |
| `0xDF38` | 22 | `KL30_SPANNUNG` | Current voltage at terminal 30 of the charging electronics | 1 |
| `0xDF3C` | 22 | `LADEBETRIEBSDAUER` | Charger total charging operating time in minutes | 1 |
| `0xDF3D` | 22 | `SOFTWAREVERSION_LADEELEKTRONIK` | SW version of the charger electronics | 1 |

## ActiveHybrid 3/5/7 (F30/F10/F01) — SME (HV battery management)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xAD61` | 31 | `ISOLATION` | Isolation test result | 2 |
| `0xAD66` | 31 | `KAPAZITAET_BESTIMMUNG` | Determination of the capacity | 2 |
| `0xDD60` | 22 | `SCHUETZ_SCHALTER` | Status of the contactor switches: closed or open. See table TAB_SCHUETZ_SCHALTER for results | 1 |
| `0xDD61` | 2E;22 | `SCHUETZ_FREIGABE` | Writes or reads the bit to enable or disable the contactor switch. Job is clamp-safe | 2 |
| `0xDD63` | 22 | `SCHUETZSCHALTUNGEN_ANZAHL` | Number of switchings of the contactor switch (currentless and under load) | 2 |
| `0xDD64` | 22 | `HVIL` | HVIL test result | 1 |
| `0xDD66` | 22 | `HV_SPANNUNG` | DC link voltage upstream of the contactors, independent of contactor state | 1 |
| `0xDD67` | 22 | `ANZAHL_KUEHLANFORDERUNG_DRINGEND` | Number of higher T states in consecutive terminal cycles. | 1 |
| `0xDD68` | 22 | `HV_SPANNUNG_BERECHNET` | Battery voltage behind the contactors, regardless of the contactor status | 1 |
| `0xDD69` | 22 | `HV_STROM` | HV current in A | 1 |
| `0xDD6A` | 22 | `ISOLATIONSWIDERSTAND` | Reading out the currently applied insulation resistance | 4 |
| `0xDD6B` | 22 | `TEMP_SENSOREN` | Cell temperature | 8 |
| `0xDD6C` | 22 | `KUEHLKREISLAUF_TEMP` | Temperature of the coolant medium in °C | 1 |
| `0xDD6E` | 2E | `SCHUETZE_MAX_SOC_SICHERHEITABFRAGE` | Switch main contactors at SOC > 90%, password protected! | 2 |
| `0xDD6F` | 22;2E | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: Closed or open / close or open | 2 |
| `0xDD72` | 22 | `AUFSTART_VERHINDERER` | Reason for not starting the HV system | 1 |
| `0xDD73` | 22 | `CUMULATIVE_LADUNG` | The accumulated charge for charges in Ah | 1 |
| `0xDD74` | 22 | `CUMULATIVE_ENTLADUNG` | The accumulated charge for discharges in Ah | 1 |
| `0xDD76` | 22 | `STATUS_KL30C_SPANNUNG` | Voltage terminal 30C in V | 1 |
| `0xDD78` | 2E | `SOC_REKALIBRIERUNG` | Trigger the SOC recalibration procedure (0 = not active; 1 = active) | 1 |
| `0xDD79` | 2E | `SCHUETZE_MIN_SOC_SICHERHEITABFRAGE` | Switch main contactors at min SOC (< 5% SOC). Caution! This job must be protected by a security query in all follow-up tools. Not possible while driving. | 2 |
| `0xDD7B` | 22;2E | `REFERENZ_KAPAZITAET` | Read and adjust battery capacity | 2 |
| `0xDD7C` | 22 | `GW_INFO` | Warranty data | 26 |
| `0xDD7D` | 22 | `STROMGRENZEN` | Current limits | 2 |
| `0xDD7E` | 22 | `SPANNUNGSGRENZEN` | Voltage limits | 2 |
| `0xDD8E` | 22 | `HVB_HISTORIE_ZYKLEN` | Output of the number of charge/discharge strokes (Ah throughput) in the respective class and output of the current load (current histogram) | 28 |
| `0xDD90` | 22 | `ZEIT_TEMP_HISTOGRAMM` | Time in various temperature classes and main contactor states | 28 |
| `0xDD91` | 22 | `ZEIT_SOC_KLASSE` | Time since installation in SOC classes | 12 |
| `0xDD94` | 22 | `HV_BATT_HIST_SOC_T1` | Duration at temperature <-20°C and at varying values of current and SOC | 70 |
| `0xDD95` | 22 | `HV_BATT_HIST_SOC_T2` | Duration at temperature -20°C < T < -13°C and at varying values of current and SoC | 70 |
| `0xDD96` | 22 | `HV_BATT_HIST_SOC_T3` | Duration at temperature -13°C < T < -7°C and at varying values of current and SoC. | 70 |
| `0xDD97` | 22 | `HV_BATT_HIST_SOC_T4` | Duration at temperature -7°C < T < 0°C and at varying values of current and SoC | 70 |
| `0xDD98` | 22 | `HV_BATT_HIST_SOC_T5` | Duration at temperature 0°C < T < 8°C and at varying values of current and SoC. | 70 |
| `0xDD99` | 22 | `HV_BATT_HIST_SOC_T6` | Duration at temperature 8°C < T < 25°C and at varying values of current and SoC | 70 |
| `0xDD9A` | 22 | `HV_BATT_HIST_SOC_T7` | Duration at temperature 25°C < T and at varying values of current and SoC | 70 |
| `0xDDAE` | 22 | `ZELLSPANNUNG_MODUL_4` | Currently measured cell voltages, module 4 | 12 |
| `0xDDAF` | 22 | `ZELLSPANNUNG_MODUL_5` | Currently measured cell voltages, module 5 | 12 |
| `0xDDB0` | 22 | `ZELLSPANNUNG_MODUL_6` | Currently measured cell voltages, module 6 | 12 |
| `0xDDB1` | 22 | `ZELLSPANNUNG_MODUL_7` | Currently measured cell voltages, module 7 | 12 |
| `0xDDB2` | 22 | `ZELLSPANNUNG_MODUL_8` | Currently measured cell voltages, module 8 | 12 |
| `0xDDB3` | 22 | `LADUNGSMENGE_HV_BOOST_RECUP` | Status of charge quantity drawn or supplied | 2 |
| `0xDDB4` | 22 | `HV_SPANNUNG_BATTERIE` | Battery voltage behind the contactors, regardless of the contactor status | 1 |
| `0xDDB6` | 22 | `ALTERUNG_INNENWIDERSTAND` | Aging of the internal resistance in percent: Internal resistance of the storage tank when new is related to the current value of the internal resistance (R_neu / R_akt) * 100 (100% = new condition, decreases with aging) | 1 |
| `0xDDB7` | 22 | `ALTERUNG_KAPAZITAET` | Remaining capacity of the battery (storage), percentage value: ( C_akt/C_nenn(neu) ) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDB9` | 22 | `ZELLSPANNUNG_MODUL_1` | Currently measured cell voltages in V, module 1 | 12 |
| `0xDDBA` | 22 | `ZELLSPANNUNG_MODUL_2` | Currently measured cell voltages, module 2 | 12 |
| `0xDDBB` | 22 | `ZELLSPANNUNG_MODUL_3` | Currently measured cell voltages in V, module 3 | 12 |
| `0xDDBC` | 22 | `ANZEIGE_SOC` | current advertisement Soc | 3 |
| `0xDDBD` | 22 | `SERVICE_DISCONNECT` | Status Service Disconnect (0 = open, 1 = closed) | 1 |
| `0xDDBE` | 22 | `VORLADUNG` | Info about time, current and temperatures during pre-charging | 15 |
| `0xDDBF` | 22 | `ZELLSPANNUNGEN_MIN_MAX` | minimum and maximum single cell voltages are output | 2 |
| `0xDDC0` | 22 | `TEMPERATUREN` | Output of minimum measured temperature, maximum measured temperature, average measured temperature, maximum cell core temperature | 4 |
| `0xDDC1` | 2E;22 | `CSC_IDS` | Hardware IDs of the individual CSCs (Cell Supervisory Circuit) | 9 |
| `0xDDC2` | 22 | `ALTERUNG_PARAMETER` | Correction factor of the series ohmic resistance during discharge. | 6 |
| `0xDDC4` | 2E;22 | `SOC` | Read out SOC value (in%) and plausibility or specification of the SOC value (0-100%) | 4 |
| `0xDDC5` | 22 | `MODULSPANNUNG_UNPLAUSIBEL` | Returns the module number of the CSCs in which an implausible voltage value was detected (linked to DTC). Return value is a component vector (length 8) with assignment 0 = no fault, 1 = fault detected. | 8 |
| `0xDDC6` | 22 | `HISTO_SYM_DAUER` | Read the number of cell balancing events in the respective time classes (target time during which the balancing resistors are to be switched active). | 8 |
| `0xDDC7` | 22 | `HISTO_SYM_ZELLANZAHL` | Read the number of sleep events in which the respective cell count was commanded for cell balancing. | 8 |
| `0xDDC8` | 22 | `SYM_DELTASOC` | Maximum SoC difference in% over the entire HVS. Ring memory of the last 5 trips | 5 |
| `0xDDC9` | 22 | `MAX_SYM_DAUER` | Maximum symmetry duration of the last symmetrization process | 15 |
| `0xDDCA` | 22 | `SERIENNUMMER_ECU` | Serial number of the SME control unit | 1 |
| `0xDDCB` | 22 | `SOC_GRENZEN` | Reading and changing the SOC limits | 2 |
| `0xDDCC` | 22;2E | `SCHUETZ_RESTZAEHLER` | Read out or reset (0 = no reset; 1 = reset) of the counter for the possible switching of contactors K1, K2, K3 | 4 |
| `0xDDCD` | 2E | `CC_MELDUNG` | Activation / deactivation of the sending of CC messages (0 = sending not active; 1 = sending active) | 1 |
| `0xDDCF` | 22 | `DIFFERENZ_SPANNUNGEN` | Differential voltage: total battery voltage - sum of cell voltages | 2 |
| `0xDDE8` | 22 | `ALTERUNG_KAPAZITAET_DEGRADATION` | Number of age-related stress degradations | 2 |
| `0xDDE9` | 22 | `ALTERUNG_KAPAZITAET_HISTOGRAMM_SOC_HUB` | Histogram with the frequency of individual SoC strokes that occurred during the operating period | 24 |
| `0xDF60` | 22 | `BETRIEBSSTUNDEN` | Time for closed main switches and total battery lifetime (closed + open time of the main switches) | 2 |
| `0xDF61` | 2E | `SOC_GRENZE_OBEN` | Opening/resetting the upper SOC limit | 2 |
| `0xDF62` | 22 | `COOL_DOWN` | Number of CoolDown scenarios (departure with hot HV storage) | 1 |
| `0xDF63` | 22 | `KLEMMENZYKLEN` | Number of terminal cycles | 1 |
| `0xDF64` | 22 | `KUEHLDAUER` | HV battery cooling time | 4 |
| `0xDF65` | 22 | `TEMP_SPREIZUNG_SYSTEM` | Time in different dT classes with active cooling | 5 |
| `0xDF66` | 22 | `TEMP_KUEHLMITTEL` | Time in different temperature classes of the coolant | 6 |
| `0xDF67` | 22 | `LADUNG_KUEHLUNG` | Charge quantities with cooling switched on | 2 |
| `0xF190` | 22 | `VIN` | 17-digit vehicle identification number, 00000000000000000 if no VIN is present (virgin ECU). Note: the result value 00000000000000000 is returned if the CAS returns 0xFF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF in the response telegram. | 1 |
| `0x6334` | 22 | `ALTERUNG_INNENWIDERSTAND_TS` | Aging of the internal resistance in percent: Internal resistance of the storage tank when new is related to the current value of the internal resistance (R_neu / R_akt) * 100 (100% = new condition, decreases with aging) | 1 |
| `0x6335` | 22 | `ALTERUNG_KAPAZITAET_TS` | Remaining capacity of the battery (storage), percentage value: ( C_akt/C_nenn(neu) ) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0x6500` | 2E | `_SOC_GRENZEN` | State of charge limit values | 2 |
| `0x6501` | 2E | `_ISOLATION` | Insulation monitoring | 2 |
| `0x6502` | 2E | `_UEBERLAST_SCHWELLE` | Charge and discharge current limits | 2 |
| `0x6503` | 2E | `_KURZSCHLUSS_STROMGRENZE` | Short circuit current limit | 2 |
| `0x6504` | 2E | `_LADE_SPANNUNGSGRENZE` | Load voltage limit | 2 |
| `0x6506` | 2E | `_SCHUETZ_K1` | K1 contactor | 2 |
| `0x6507` | 2E | `_SCHUETZ_K2` | K2 contactor | 2 |
| `0x6508` | 2E | `_SCHUETZ_K3` | K3 contactor | 2 |
| `0x6509` | 2E | `_SERIENNUMMER` | HV battery (storage) serial number | 2 |
| `0x650B` | 2E | `_ENTLADE_SPANNUNGSGRENZE` | Discharge voltage limit | 2 |
| `0x6511` | 2E | `_SYM_MODUS` | Symmetry mode of the SEM | 2 |
| `0x6512` | 2E | `_MESSBOTSCHAFTEN` | Switch measurement messages on / off | 2 |
| `0x6515` | 2E | `_CSC_INDIZIERUNG` | CSCs are re-indexed using the position indices passed as an argument | 2 |
| `0x6516` | 22 | `_ST_SYM_MODUS` | Status of the balancing | 1 |
| `0x6519` | 2E | `_CSC_STANDBY` | Put CSCs in standby mode | 2 |
| `0x651B` | 2E | `_ANFORDERUNG_SCHUETZE_SCHLIESSEN` | Close contactor | 2 |

## ActiveHybrid 3/5/7 (F30/F10/F01) — EME (E-machine electronics)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x1721` | 22 | `RESET_REASON` | Values for the reset reason. The values are to be defined by the supplier. Default value: 0xFF. Note: this DID is optional, but must at least be populated with 0xFF on reset. | 8 |
| `0xADF0` | 31 | `EME_ROTORLAGESENSOR_ANLERNEN` | Learn rotor position sensor | 2 |
| `0xADF1` | 31 | `EME_DCDC_WANDLER` | Control or read the status of the DC / DC converter | 8 |
| `0xADF2` | 31 | `EME_HV_SYSTEM_ON_OFF` | Run the HV system up / down | 2 |
| `0xADF3` | 31 | `EME_EWAP` | Control of the LIN water pump EME with specification of the speed and control time | 3 |
| `0xADF4` | 31 | `EME_AKS_EMK` | Command the electric machine in the AKS: 0 - Control on EME-SW; 1 - AKS E-machine requested | 2 |
| `0xADF5` | 31 | `EME_EEP_RECALL_DEFAULT` | Reset the NV memory of the HYM in the EME, stop the reset, or read the status of the clearing operations 0 - clear NV-RAM not requested; 1 - clear NV-RAM requested | 1 |
| `0xADF7` | 31 | `EME_IGBT_FREILAUF` | Opening the IGBTs to switch the e-machine to high impedance on the AC side | 1 |
| `0xDDF0` | 22 | `EME_TEMP_EMASCHINE` | Read the current temperature value of the e-machine in degrees Celsius | 5 |
| `0xDDF1` | 22 | `EME_SPANNUNG_DC_HV` | DC voltage of the e-machine after rectification by the EME (HV battery side, referred to internal) | 1 |
| `0xDDF2` | 22 | `EME_SPANNUNG_DC_HV_DCDC` | High-voltage vehicle electrical system voltage measured by the DC/DC converter (in the EME) | 1 |
| `0xDDF3` | 22 | `EME_STROM_EMASCHINE_AC` | HV current of the DC/DC converter and the averaged RMS current of the e-machine | 2 |
| `0xDDF4` | 22 | `EME_STROM_EMASCHINE_DC` | DC current (on the HV side) caused by the EMK | 1 |
| `0xDDF5` | 22 | `EME_POSITIONSGEBER` | Angular position of the e-machines in degrees | 1 |
| `0xDDF6` | 22 | `EME_DCDC_LV` | Voltage / current DCDC (12V vehicle electrical system) at the B + bolt | 2 |
| `0xDDF7` | 22 | `EME_ELEKTRISCHE_MASCHINE` | Read speed and torque of the e-machine | 3 |
| `0xDDF8` | 22 | `EME_DCDC_LADEMODUS` | Query the DC/DC converter for operating mode and battery state of charge | 2 |
| `0xDDF9` | 22 | `EME_EPSOFFSET` | EPS offset (-180.00° .. +180.00°) | 1 |
| `0xDDFC` | 22 | `EME_INFO_EMK` | Bit-coded derating information from the e-machine control | 1 |
| `0xDDFD` | 2E | `EME_DME_LEERLAUFREGELUNG_AKTIVIEREN` | Activation/deactivation of idle speed control on the DME | 1 |
| `0xDDFE` | 22;2E | `EME_ANTRIEBSART` | Current hybrid operating mode and EME operating mode control | 2 |
| `0xDDFF` | 2E | `EME_ELEKTRISCHE_MASCHINE_GENERATORBETRIEB` | Set generator mode of the e-machine or control via EME software | 1 |
| `0xDE00` | 22 | `EME_HVPM_DCDC_ANSTEUERUNG` | Return values from the HVPM for DCDC control | 16 |
| `0xDE01` | 22 | `EME_HVPM_VERBRAUCHERREDUZIERUNG` | Return values for HVPM consumer reduction | 9 |
| `0xDE02` | 22 | `EME_HVPM_HV_SYSTEM_ON_OFF` | High-voltage system on / off | 7 |
| `0xDE03` | 22 | `EME_HVPM_ENERGIEBORDNETZ` | Return values of the HVPM for HV energy and cell voltages | 34 |
| `0xDE04` | 22 | `EME_HVPM_ENERGIEBORDNETZ_2` | Number of times the vehicle was ready to drive in the SOC area | 14 |
| `0xDE05` | 22 | `EME_HVPM_MSA` | HVPM engine start-stop automatic | 39 |
| `0xDE06` | 22 | `EME_HVPM_PKOR` | HVPM performance coordinator | 24 |
| `0xDE07` | 2E | `EME_HVPM_INFOSPEICHER_MSA_LOESCHEN` | All fault memory entries from diagnostic job STATUS_HVPM_MSA are set to zero. | 1 |
| `0xDE08` | 2E | `EME_HVPM_INFOSPEICHER_PKOR_LOESCHEN` | All fault memory entries of diagnostic job STATUS_HVPM_EKMV are set to zero. | 1 |
| `0xDE09` | 2E | `EME_HVPM_INFOSPEICHER_STRZLR_LOESCHEN` | Clear the info memory HSPM (STRZL) | 1 |
| `0xDE0A` | 2E | `EME_HVPM_INFOSPEICHER_SPMON_LOESCHEN` | Deleting the information memory HVPMP (SPMON) | 1 |
| `0xDE0B` | 22 | `EME_HV_ISOLATION` | External insulation fault, SME | 1 |
| `0xDE0C` | 22 | `EME_HVIL_GESAMT` | Reading out the HVIL status in the EME; if HVIL is interrupted, then not ok | 1 |
| `0xDE0D` | 22 | `EME_LV_BAT` | Status of the LV battery | 3 |
| `0xDE0E` | 22 | `EME_ANSTEUERUNG_ELUP` | Current switching status ELUP (0 - off; 1 - on) | 1 |
| `0xDE0F` | 22 | `EME_KL30C_SPANNUNG` | 0 = crash not detected, 1 = crash detected | 1 |
| `0xDE10` | 22 | `EME_HVB_TAUSCH_LESEN` | Odometer reading (km) of the last battery replacement | 2 |
| `0xDE12` | 22 | `EME_PUMPEN` | Actual speed of the coolant pump | 1 |
| `0xDE13` | 22 | `EME_BETRIEBSART_HYBRID` | Hybrid operating mode (Ba_hybrid) is output | 1 |
| `0xDE14` | 22 | `EME_ANF_NL` | Read out history memory of St_anf_nl_eme | 48 |
| `0xDE15` | 22 | `EME_NLM_DEAK` | Read out history memory of St_nlm_deakt_msa | 48 |
| `0xDE17` | 2E | `EME_NLM_INFO_ERS_LOESCHEN` | Reset history memory of NLM info substitute reactions to zero | 1 |
| `0xDE18` | 22 | `EME_HVPM_SPANNUNGSFREIHEIT` | Info memory for the de-energized state of the high-voltage system (monitored by HVPM) | 40 |
| `0xDE19` | 22 | `EME_ELUP` | Number of brake actuations, running time and starts of the ELUP | 3 |
| `0xDE1A` | 22 | `EME_12VBATT_ENTL_STANDKL` | Charge quantity | 1 |
| `0xDE1B` | 22 | `EME_HVPM_MSA_2` | HVPM MSA2 | 10 |
| `0xDE1C` | 22 | `EME_HVPM_DCDC_ALS` | HVPM DCDC ALS | 4 |
| `0xDE1E` | 22 | `EME_SZE_ZSEBATTERIE` | Read out the results of the ZSE battery state-detection | 46 |
| `0xDE1F` | 2E | `EME_TAUSCH_ZSEBATT_REGISTRIEREN` | Register ZSE battery replacement: 0 = no request; 1 = register ZSE battery replacement | 1 |
| `0xDE20` | 2E | `EME_ZSEBATT_SZEWERTE_LOESCHEN` | Reset all histograms, counters, etc. of the ZSE battery | 1 |
| `0xDE21` | 22 | `EME_TEMP_DCDC` | Current temperature value of the DC/DC converter transformer | 1 |
| `0xDE22` | 22 | `EME_KAELTEMITTEL_ABSPERRVENTIL_ON_OFF` | Status of the refrigerant shut-off valve; 0 = valve closed; 1 = valve open | 1 |
| `0xDE23` | 2E | `EME_KAELTEMITTEL_ABSPERRVENTIL` | Control of the refrigerant shut-off valve | 1 |
| `0xDE24` | 22 | `EME_SCHALTSPIELE_ZSE_RELAIS` | Number of relay switching cycles of the ZSE branch | 1 |
| `0xDE25` | 22;2E | `EME_ZSE_RELAIS` | Activate the ZSE relay manually | 2 |
| `0xDE26` | 22 | `EME_HVSTART_FEHLER` | Indication of the fault when starting up the HV system | 1 |
| `0xDE27` | 22 | `EME_EM_TEMP_HIST` | Read e-machine temperature histogram | 6 |
| `0xDE28` | 22 | `EME_EBS_1` | Read out teleservice data | 32 |
| `0xDE29` | 2E;22 | `EME_NOTENTL_ZAEHLER` | Emergency discharge counter: counter status / reset counter (0 = no reset; 1 = reset) | 2 |
| `0xDE2A` | 22 | `EME_FELDDATEN_LESEN` | Read out field data of the EME | 11 |
| `0xDE2B` | 2E | `EME_RESET_EM_TEMPHIST` | Reset the temperature histogram of the EMM | 1 |
| `0xDE2C` | 22 | `EME_EBS_2` | Read teleservice data 2 | 56 |
| `0xDE2E` | 22 | `EME_SERIENNUMMERN_BOSCH` | Serial, part and revision number of the ECU (Bosch) | 4 |
| `0xDE2F` | 22 | `EME_SOH_LESEN` | SOH of the EME over lifetime | 1 |
| `0xDEC0` | 22 | `KAELTEMITTEL_ABSPERRVENTIL_ON_OFF_PWM` | Status of the refrigerant shut-off valve; 0% = valve closed; 100% = valve open | 1 |
| `0xDEC2` | 22 | `SPANNUNG_ELUP` | Voltage level at the ELUP output of the EME | 1 |
| `0xDEC3` | 22 | `STROM_ELUP` | Voltage level at the ELUP output of the EME | 1 |
| `0xDECF` | 22 | `EME_IUMPR` | Read information on the IUMPR values stored in the ECU | 84 |
| `0x63A4` | 22 | `EME_NLK_ER_ANF` | EME_NLK_ER_ANF | 2 |
| `0x63FF` | 22 | `EME_HYM_ID` | Read out the version of the BMW library | 1 |
| `0xF50C` | 31 | `EME_EM_ANSTEUERUNG` | EME_EM_ANSTEUERUNG | 3 |

## ActiveHybrid 7 (F04) — SME (HV battery management)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xDD60` | 22 | `SCHUETZ_SCHALTER` | Contactor switch status: closed or open | 1 |
| `0xDD61` | 22;2E | `SCHUETZ_FREIGABE` | Writes or reads the bit to enable or disable the contactor switch. Job is clamp-safe | 2 |
| `0xDD63` | 22 | `SCHUETZSCHALTUNGEN_ANZAHL` | Number of switchings of the contactor switch (currentless and under load) | 1 |
| `0xDD64` | 22 | `HVIL` | Disturb/disable the interlock generator in the BMS / HVIL test result | 1 |
| `0xDD66` | 22 | `HV_SPANNUNG` | HV voltage, DC-link voltage before the contactors | 1 |
| `0xDD68` | 22 | `HV_SPANNUNG_BERECHNET` | HV voltage calculated from individual cells, battery voltage behind the contactors | 1 |
| `0xDD69` | 22 | `HV_STROM` | HV electricity | 1 |
| `0xDD6A` | 22 | `ISOLATIONSWIDERSTAND` | Reading out the currently applied insulation resistance | 2 |
| `0xDD6B` | 22 | `TEMP_SENSOREN` | Cell temperature | 4 |
| `0xDD6C` | 22 | `KUEHLKREISLAUF_TEMP` | Coolant circuit temperature | 1 |
| `0xDD6D` | 22 | `KAPAZITAETSVERLUST` | HV battery capacity loss | 2 |
| `0xDD6F` | 22;2E | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: closed or open | 2 |
| `0xDD70` | 22 | `AUSLIEFERUNGSDATEN` | Read manufacturer data | 5 |
| `0xDD71` | 22 | `ZELLSPANNUNG` | Cell voltages | 35 |
| `0xDD72` | 22 | `AUFSTART_VERHINDERER` | Reason for not starting the HV system | 1 |
| `0xDD73` | 22 | `CUMULATIVE_LADUNG` | Status cumulative charge | 1 |
| `0xDD74` | 22 | `CUMULATIVE_ENTLADUNG` | Status cumulative discharge | 1 |
| `0xDD75` | 22 | `SERIENNUMMER` | Write/read serial number | 1 |
| `0xDD76` | 22 | `STATUS_KL30C_SPANNUNG` | Voltage terminal30C | 1 |
| `0xDD77` | 22 | `HISTOGRAM` | Time/temperature histogram SoC 1-3 | 18 |
| `0xDD79` | 2F | `SCHUETZE_MIN_SOC_SICHERHEITABFRAGE` | Switch main contactors at min SOC (< 5% SOC). Caution! This job must be protected by a security query in all follow-up tools. Not possible while driving. Also still possible at deep discharge (5% SOC). Caution! This job must be protected by a security query in all follow-up tools, to make sure a charger is already connected! | 2 |
| `0xDD7B` | 22;2E | `REFERENZ_KAPAZITAET` | Read and adjust battery capacity | 2 |
| `0xDD7C` | 22 | `GW_INFO` | Warranty data | 52 |
| `0xDD7D` | 22 | `STROMGRENZEN` | Current limits | 2 |
| `0xDD7E` | 22 | `SPANNUNGSGRENZEN` | Voltage limits | 2 |
| `0xDD7F` | 22;2E | `OCV_KENNLINIE` | SoC-dependent open-circuit voltage | 42 |
| `0xAD60` | 31 | `ZELLAUSGLEICHSENTLADESPANNUNG` | Cell balancing discharge voltage | 7 |
| `0xAD61` | 31 | `ISOLATION` | Isolation test result | 1 |
| `0xAD62` | 31 | `SOC` | HV battery SOC (state of charge) | 4 |
| `0xDD64` | 22;2F | `HVIL` | Disturb/disable the interlock generator in the BMS / HVIL test result | 2 |
| `0xDD6F` | 2E;22 | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: closed or open | 2 |
| `0xDD7F` | 2E | `OCV_KENNLINIE` | still to be defined | 2 |
| `0xDD7A` | 2F | `SCHUETZE_MAX_SOC` | Switch main contactors in normal operating state (>95% SOC). Not possible while driving. Also still possible at high state of charge (> 95% SOC). | 1 |
| `0xDD78` | 2F | `SCHUETZE_MIN_SOC` | Switch main contactors at min SOC (10% - 5% SOC). Not possible while driving! Only possible between 10% and 5% SOC! | 1 |
| `0xDD6D` | 22 | `SOH` | HV battery SOH (state of health) | 2 |
| `0xDAFE` | 22 | `STATUS_KLEMME_15_EIN` | Returns status of the terminal(s) in the ECU: 0=OFF; 1=ON | 1 |

## ActiveHybrid 7 (F04) — EME (E-machine electronics)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x6300` | 22 | `STATUS_EPSOFFSET` | EPS offset -180.00° .. +180.00° | 1 |
| `0x6301` | 22 | `STATUS_TEMPERATUREN` | Read temperatures from the e-motor DCB (power stage) control board | 9 |
| `0x6302` | 22 | `STATUS_HVIL_GESAMT` | Read the HVIL status; if HVIL is interrupted, then not OK | 1 |
| `0x6303` | 22 | `STATUS_HV_ISOLATION` | Read the insulation monitor; if insulation fault, then not OK | 1 |
| `0x6304` | 22 | `STATUS_PRECHARGE` | Variable in the base SW: ECUM_eSystemState = Run -> precharge complete. However, precharge is performed by the SME | 1 |
| `0x6305` | 22 | `STATUS_SPANNUNG_DC_HV` | DC voltage of the EMK EMR (HV battery side) (referred to internal) | 1 |
| `0x6306` | 22 | `STATUS_HV_STROM` | HV current, electrical system (Bordnetz) | 4 |
| `0x6307` | 22 | `STATUS_POSITIONSGEBER` | Angular position of the e-machines in degrees | 1 |
| `0x6308` | 22 | `STATUS_LV_BAT` |  | 3 |
| `0x6309` | 22 | `STATUS_ELEKTRISCHE_MASCHINE` |  | 3 |
| `0x630A` | 22 | `STATUS_DCDC_LADEMODUS` |  | 2 |
| `0x630B` | 22;2E | `STATUS_EME_ANTRIEBSART` | Selection: normal, explicitly no e-machine assist, set positive torque limits to zero, Md_em1_max_1s/10s_pm. Implemented in function P_emko_emlim | 2 |
| `0x6310` | 22 | `STATUS_KL30C_SPANNUNG` |  | 1 |
| `0x630D` | 22 | `STATUS_PUMPEN` |  | 1 |
| `0x6313` | 22 | `STATUS_TEMPERATUR_HVB` |  | 1 |
| `0x6314` | 22 | `STATUS_TEMP_DCDC` |  | 3 |
| `0x6315` | 22 | `STATUS_SPANNUNG_DC_HV_DCDC` |  | 1 |
| `0x6316` | 22 | `STATUS_EMK_STROM_DC` |  | 2 |
| `0x6317` | 22 | `STATUS_DCDC_LV` |  | 1 |
| `0x6318` | 22 | `STATUS_EPI` |  | 4 |
| `0x6319` | 22 | `STATUS_ERSTSTARTBEGRENZUNG` |  | 1 |
| `0x631A` | 22 | `STATUS_INFO_EMK` |  | 1 |
| `0x6320` | 22 | `STATUS_HVPM_DC/DC_ANSTEUERUNG` |  | 17 |
| `0x6321` | 22 | `STATUS_HVPM_VERBRAUCHERREDUZIERUNG` |  | 11 |
| `0x6322` | 22 | `STATUS_HVPM_HV_SYSTEM_ON_OFF` |  | 13 |
| `0x6323` | 22 | `STATUS_HVPM_ENERGIEBORDNETZ` |  | 34 |
| `0x6324` | 22 | `STATUS_HVPM_MSA` |  | 45 |
| `0x6325` | 22 | `STATUS_HVPM_PKOR` |  | 23 |
| `0x6326` | 22 | `STATUS_REFERENZKAPAZITAET_HVB` |  | 1 |
| `0x6327` | 22 | `STATUS_SOC_HVB` |  | 1 |
| `0x632A` | 22 | `STATUS_RUHESPANNUNG` |  | 1 |
| `0x632B` | 22 | `STATUS_ESOC_SOC` |  | 1 |
| `0x632C` | 22 | `STATUS_LADUNGSMENGE_HVB` |  | 1 |
| `0x632D` | 22 | `STATUS_HVB_TAUSCH_LESEN` |  | 2 |
| `0x632E` | 22 | `STATUS_HVB_LADUNGSMENGE` |  | 4 |
| `0x6334` | 22 | `STATUS_ALTERUNG_INNENWIDERSTAND` |  | 1 |
| `0x6335` | 22 | `STATUS_ALTERUNG_KAPAZITAET` |  | 1 |
| `0x6336` | 22 | `STATUS_HVB_WARRANTY` |  | 7 |
| `0x6351` | 22 | `STATUS_ENTLADE_INNENWIDERSTAND_T1` |  | 5 |
| `0x6352` | 22 | `STATUS_ENTLADE_INNENWIDERSTAND_T2` |  | 5 |
| `0x6353` | 22 | `STATUS_ENTLADE_INNENWIDERSTAND_T3` |  | 5 |
| `0x6354` | 22 | `STATUS_ENTLADE_INNENWIDERSTAND_T4` |  | 5 |
| `0x6355` | 22 | `STATUS_ENTLADE_INNENWIDERSTAND_T5` |  | 5 |
| `0x6356` | 22 | `STATUS_ENTLADE_INNENWIDERSTAND_T6` |  | 5 |
| `0x6357` | 22 | `STATUS_ENTLADE_INNENWIDERSTAND_T7` |  | 5 |
| `0x6358` | 22 | `STATUS_LADE_INNENWIDERSTAND_T1` |  | 5 |
| `0x6359` | 22 | `STATUS_LADE_INNENWIDERSTAND_T2` |  | 5 |
| `0x635A` | 22 | `STATUS_LADE_INNENWIDERSTAND_T3` |  | 5 |
| `0x635B` | 22 | `STATUS_LADE_INNENWIDERSTAND_T4` |  | 5 |
| `0x635C` | 22 | `STATUS_LADE_INNENWIDERSTAND_T5` |  | 5 |
| `0x635D` | 22 | `STATUS_LADE_INNENWIDERSTAND_T6` |  | 5 |
| `0x635E` | 22 | `STATUS_LADE_INNENWIDERSTAND_T7` |  | 5 |
| `0x635F` | 22 | `STATUS_MITTELWERT_RI_FAKTOR_1S` |  | 1 |
| `0x6360` | 22 | `STATUS_MITTELWERT_RI_FAKTOR_5S` |  | 1 |
| `0x6361` | 22 | `STATUS_ANZEIGE_SOC` |  | 1 |
| `0x636D` | 22 | `STATUS_HVB_HISTORIE_STROMBELASTUNG` |  | 8 |
| `0x636E` | 22 | `STATUS_HVB_HISTORIE_TEMPERATUR` |  | 8 |
| `0x636F` | 22 | `STATUS_HVB_HISTORIE_SOC_SEIT_EINBAU` |  | 8 |
| `0x6370` | 22 | `STATUS_HVPM_ENERGIEBORDNETZ_2` |  | 14 |
| `0x63A2` | 22 | `STATUS_KALTSTARTZAEHLER` |  | 4 |
| `0x63A3` | 22 | `STATUS_BETRIEBSART_HYBRID` |  | 1 |
| `0x63A4` | 22 | `STATUS_NLK_ER_ANF` |  | 3 |
| `0x63A5` | 22 | `STATUS_HVPM_SPANNUNGSFREIHEIT` |  | 40 |
| `0x636B` | 22 | `STATUS_HVB_HISTORIE_SOC_LADEHUEBE` |  | 10 |
| `0x636C` | 22 | `STATUS_HVB_HISTORIE_SOC_ENTLADEHUEBE` |  | 10 |
| `0x63A6` | 22 | `STATUS_HV_BATT_HIST_SOC1_T1` |  | 10 |
| `0x63A7` | 22 | `STATUS_HV_BATT_HIST_SOC2_T1` |  | 10 |
| `0x63A8` | 22 | `STATUS_HV_BATT_HIST_SOC3_T1` |  | 10 |
| `0x63A9` | 22 | `STATUS_HV_BATT_HIST_SOC4_T1` |  | 10 |
| `0x63AA` | 22 | `STATUS_HV_BATT_HIST_SOC5_T1` |  | 10 |
| `0x63AB` | 22 | `STATUS_HV_BATT_HIST_SOC6_T1` |  | 10 |
| `0x63AC` | 22 | `STATUS_HV_BATT_HIST_SOC7_T1` |  | 10 |
| `0x63AD` | 22 | `STATUS_HV_BATT_HIST_SOC1_T2` |  | 10 |
| `0x63AE` | 22 | `STATUS_HV_BATT_HIST_SOC2_T2` |  | 10 |
| `0x63AF` | 22 | `STATUS_HV_BATT_HIST_SOC3_T2` |  | 10 |
| `0x63B0` | 22 | `STATUS_HV_BATT_HIST_SOC4_T2` |  | 10 |
| `0x63B1` | 22 | `STATUS_HV_BATT_HIST_SOC5_T2` |  | 10 |
| `0x63B2` | 22 | `STATUS_HV_BATT_HIST_SOC6_T2` |  | 10 |
| `0x63B3` | 22 | `STATUS_HV_BATT_HIST_SOC7_T2` |  | 10 |
| `0x63B4` | 22 | `STATUS_HV_BATT_HIST_SOC1_T3` |  | 10 |
| `0x63B5` | 22 | `STATUS_HV_BATT_HIST_SOC2_T3` |  | 10 |
| `0x63B6` | 22 | `STATUS_HV_BATT_HIST_SOC3_T3` |  | 10 |
| `0x63B7` | 22 | `STATUS_HV_BATT_HIST_SOC4_T3` |  | 10 |
| `0x63B8` | 22 | `STATUS_HV_BATT_HIST_SOC5_T3` |  | 10 |
| `0x63B9` | 22 | `STATUS_HV_BATT_HIST_SOC6_T3` |  | 10 |
| `0x63BA` | 22 | `STATUS_HV_BATT_HIST_SOC7_T3` |  | 10 |
| `0x63BB` | 22 | `STATUS_HV_BATT_HIST_SOC1_T4` |  | 10 |
| `0x63BC` | 22 | `STATUS_HV_BATT_HIST_SOC2_T4` |  | 10 |
| `0x63BD` | 22 | `STATUS_HV_BATT_HIST_SOC3_T4` |  | 10 |
| `0x63BE` | 22 | `STATUS_HV_BATT_HIST_SOC4_T4` |  | 10 |
| `0x63BF` | 22 | `STATUS_HV_BATT_HIST_SOC5_T4` |  | 10 |
| `0x63C0` | 22 | `STATUS_HV_BATT_HIST_SOC6_T4` |  | 10 |
| `0x63C1` | 22 | `STATUS_HV_BATT_HIST_SOC7_T4` |  | 10 |
| `0x63C2` | 22 | `STATUS_HV_BATT_HIST_SOC1_T5` |  | 10 |
| `0x63C3` | 22 | `STATUS_HV_BATT_HIST_SOC2_T5` |  | 10 |
| `0x63C4` | 22 | `STATUS_HV_BATT_HIST_SOC3_T5` |  | 10 |
| `0x63C5` | 22 | `STATUS_HV_BATT_HIST_SOC4_T5` |  | 10 |
| `0x63C6` | 22 | `STATUS_HV_BATT_HIST_SOC5_T5` |  | 10 |
| `0x63C7` | 22 | `STATUS_HV_BATT_HIST_SOC6_T5` |  | 10 |
| `0x63C8` | 22 | `STATUS_HV_BATT_HIST_SOC7_T5` |  | 10 |
| `0x63C9` | 22 | `STATUS_HV_BATT_HIST_SOC1_T6` |  | 10 |
| `0x63CA` | 22 | `STATUS_HV_BATT_HIST_SOC2_T6` |  | 10 |
| `0x63CB` | 22 | `STATUS_HV_BATT_HIST_SOC3_T6` |  | 10 |
| `0x63CC` | 22 | `STATUS_HV_BATT_HIST_SOC4_T6` |  | 10 |
| `0x63CD` | 22 | `STATUS_HV_BATT_HIST_SOC5_T6` |  | 10 |
| `0x63CE` | 22 | `STATUS_HV_BATT_HIST_SOC6_T6` |  | 10 |
| `0x63CF` | 22 | `STATUS_HV_BATT_HIST_SOC7_T6` |  | 10 |
| `0x63D0` | 22 | `STATUS_HV_BATT_HIST_SOC1_T7` |  | 10 |
| `0x63D1` | 22 | `STATUS_HV_BATT_HIST_SOC2_T7` |  | 10 |
| `0x63D2` | 22 | `STATUS_HV_BATT_HIST_SOC3_T7` |  | 10 |
| `0x63D3` | 22 | `STATUS_HV_BATT_HIST_SOC4_T7` |  | 10 |
| `0x63D4` | 22 | `STATUS_HV_BATT_HIST_SOC5_T7` |  | 10 |
| `0x63D5` | 22 | `STATUS_HV_BATT_HIST_SOC6_T7` |  | 10 |
| `0x63D6` | 22 | `STATUS_HV_BATT_HIST_SOC7_T7` |  | 10 |
| `0x63D7` | 22 | `STATUS_12VBATT_ENTL_STANDKL` |  | 1 |
| `0x63D8` | 22 | `STATUS_HVPM_MSA_2` |  | 13 |
| `0x63D9` | 22 | `STATUS_HVPM_DCDC_ALS` |  | 4 |
| `0x63DA` | 22 | `STATUS_ANF_NL` |  | 48 |
| `0x63DB` | 22 | `STATUS_NLM_DEAK` |  | 48 |
| `0x63DC` | 22 | `STATUS_NLM_ERREAKT` |  | 48 |
| `0x6362` | 22 | `STATUS_MAXIMALER_ANZEIGE_SOC` |  | 1 |
| `0x6363` | 22 | `STATUS_MINIMALER_ANZEIGE_SOC` |  | 1 |
| `0x6369` | 22 | `STATUS_HVB_HISTORIE_MIN_SOC` |  | 6 |
| `0x636A` | 22 | `STATUS_HVB_HISTORIE_MAX_SOC` |  | 6 |
| `0x63DD` | 22 | `STATUS_TA_PRUEFSTAND` |  | 108 |
| `0x63DE` | 22 | `STATUS_RLS_SINUS_COSINUS` |  | 5 |
| `0xF500` | 31 | `STEUERN_ROTORLAGESENSOR_ANLERNEN` |  | 3 |
| `0xF502` | 31 | `STEUERN_DCDC_WANDLER` | RIDI_DCDC - Control of the HV voltage of the DC/DC converter | 9 |
| `0xF503` | 31 | `STEUERN_HV_SYSTEM_ON_OFF` | RIDI_HYSYS - Power up/power down HV system | 2 |
| `0xF504` | 31 | `STEUERN_EME_PUMPE` | RIDI_EMECWP5 - Coolant pump speed request for the EME | 2 |
| `0xF505` | 2E | `STEUERN_DME_LEERLAUFREGELUNG_AKTIVIEREN` | RIDI_DMELLR - Activate DME idle speed controller | 1 |
| `0xF506` | 2E | `STEUERN_ELEKTRISCHE_MASCHINE_GENERATORBETRIEB` | RIDI_EMGENERATOR set negative torque limits to zero, Md_em1_min_1s/10s_pm. Implemented in function P_emko_emlim | 1 |
| `0xF507` | 2E | `STEUERN_HVPM_INFOSPEICHER_STRZLR_LOESCHEN` | RIDI_HVPM_STRZLR_CLR - Clear HSPM info memory | 1 |
| `0xF508` | 2E | `STEUERN_HVPM_INFOSPEICHER_SPMON_LOESCHEN` | RIDI_HVPM_SPMON_CLR - Clear HVPM info memory | 1 |
| `0xF509` | 31 | `STEUERN_ENTLADEMODUS` | RIDI_ENTLADEMODUS - Contactors must be closed and battery temperature above 10°C and terminal 15 on, no gear engaged | 5 |
| `0xF50A` | 31 | `STEUERN_LADEMODUS` | RIDI_LADEMODUS - Contactors must be closed and battery temperature above 10°C and terminal 15 on, no gear engaged | 5 |
| `0xF50B` | 2E | `STEUERN_REFERENZKAPAZITAET_HVB` | RIDI_REFKAP_HVB - The reference capacity determined on the tester is written to the EME | 1 |
| `0xF50C` | 31 | `STEUERN_ELEKTRISCHE_MASCHINE` | RIDI_EMASCHINE - CONTROL_ELECTRIC_MACHINE is used to set the operating mode of the e-machine (torque or speed request) and to specify the torque or the speed. Operating mode = 0 --> torque request Md_em1_soll_steuern; operating mode = 1 --> speed request N_em1_soll_steuern | 3 |
| `0xF50D` | 2E | `STEUERN_HVPM_INFOSPEICHER_MSA_LOESCHEN` | RIDI_HVPM_MSA_CLR - Reset all info memory entries from job STATUS_HVPM_MSA to zero | 1 |
| `0xF50E` | 2E | `STEUERN_HVPM_INFOSPEICHER_PKOR_LOESCHEN` | RIDI_HVPM_PKOR_CLR - Reset all info memory entries from job STATUS_HVPM_EKMV to zero | 1 |
| `0xF50F` | 31 | `STEUERN_EEP_RECALL_DEFAULT` | Reset the ZFS EEPROM parameters to default values | 0 |
| `0xF510` | 2E | `STEUERN_NLM_INFO_ERS_LOESCHEN` | RIDI_NLM_ERS_CLR - Reset NLM info history memory of substitute responses to zero | 1 |
| `0xF511` | 31 | `STEUERN_PHASENUNTERBRECHUNG_STILLSTAND` | Phase interruption at standstill | 3 |
| `0xF512` | 31 | `STEUERN_START_DCDC_CPLD_UPDATE` | Start and status of CPLD update | 2 |
| `0x63A6` | 22 | `STATUS_HV_BATT_HIST_SOC1_ T1` |  | 10 |
| `0x63A7` | 22 | `STATUS_HV_BATT_HIST_SOC2_ T1` |  | 10 |
| `0x63A8` | 22 | `STATUS_HV_BATT_HIST_SOC3_ T1` |  | 10 |
| `0x63A9` | 22 | `STATUS_HV_BATT_HIST_SOC4_ T1` |  | 10 |
| `0x63AA` | 22 | `STATUS_HV_BATT_HIST_SOC5_ T1` |  | 10 |
| `0x63AB` | 22 | `STATUS_HV_BATT_HIST_SOC6_ T1` |  | 10 |
| `0x63AC` | 22 | `STATUS_HV_BATT_HIST_SOC7_ T1` |  | 10 |
| `0x63AD` | 22 | `STATUS_HV_BATT_HIST_SOC1_ T2` |  | 10 |
| `0x63AE` | 22 | `STATUS_HV_BATT_HIST_SOC2_ T2` |  | 10 |
| `0x63AF` | 22 | `STATUS_HV_BATT_HIST_SOC3_ T2` |  | 10 |
| `0x63B0` | 22 | `STATUS_HV_BATT_HIST_SOC4_ T2` |  | 10 |
| `0x63B1` | 22 | `STATUS_HV_BATT_HIST_SOC5_ T2` |  | 10 |
| `0x63B2` | 22 | `STATUS_HV_BATT_HIST_SOC6_ T2` |  | 10 |
| `0x63B3` | 22 | `STATUS_HV_BATT_HIST_SOC7_ T2` |  | 10 |
| `0x63B4` | 22 | `STATUS_HV_BATT_HIST_SOC1_ T3` |  | 10 |
| `0x63B5` | 22 | `STATUS_HV_BATT_HIST_SOC2_ T3` |  | 10 |
| `0x63B6` | 22 | `STATUS_HV_BATT_HIST_SOC3_ T3` |  | 10 |
| `0x63B7` | 22 | `STATUS_HV_BATT_HIST_SOC4_ T3` |  | 10 |
| `0x63B8` | 22 | `STATUS_HV_BATT_HIST_SOC5_ T3` |  | 10 |
| `0x63B9` | 22 | `STATUS_HV_BATT_HIST_SOC6_ T3` |  | 10 |
| `0x63BA` | 22 | `STATUS_HV_BATT_HIST_SOC7_ T3` |  | 10 |
| `0x63BB` | 22 | `STATUS_HV_BATT_HIST_SOC1_ T4` |  | 10 |
| `0x63BC` | 22 | `STATUS_HV_BATT_HIST_SOC2_ T4` |  | 10 |
| `0x63BD` | 22 | `STATUS_HV_BATT_HIST_SOC3_ T4` |  | 10 |
| `0x63BE` | 22 | `STATUS_HV_BATT_HIST_SOC4_ T4` |  | 10 |
| `0x63BF` | 22 | `STATUS_HV_BATT_HIST_SOC5_ T4` |  | 10 |
| `0x63C0` | 22 | `STATUS_HV_BATT_HIST_SOC6_ T4` |  | 10 |
| `0x63C1` | 22 | `STATUS_HV_BATT_HIST_SOC7_ T4` |  | 10 |
| `0x63C2` | 22 | `STATUS_HV_BATT_HIST_SOC1_ T5` |  | 10 |
| `0x63C3` | 22 | `STATUS_HV_BATT_HIST_SOC2_ T5` |  | 10 |
| `0x63C4` | 22 | `STATUS_HV_BATT_HIST_SOC3_ T5` |  | 10 |
| `0x63C5` | 22 | `STATUS_HV_BATT_HIST_SOC4_ T5` |  | 10 |
| `0x63C6` | 22 | `STATUS_HV_BATT_HIST_SOC5_ T5` |  | 10 |
| `0x63C7` | 22 | `STATUS_HV_BATT_HIST_SOC6_ T5` |  | 10 |
| `0x63C8` | 22 | `STATUS_HV_BATT_HIST_SOC7_ T5` |  | 10 |
| `0x63C9` | 22 | `STATUS_HV_BATT_HIST_SOC1_ T6` |  | 10 |
| `0x63CA` | 22 | `STATUS_HV_BATT_HIST_SOC2_ T6` |  | 10 |
| `0x63CB` | 22 | `STATUS_HV_BATT_HIST_SOC3_ T6` |  | 10 |
| `0x63CC` | 22 | `STATUS_HV_BATT_HIST_SOC4_ T6` |  | 10 |
| `0x63CD` | 22 | `STATUS_HV_BATT_HIST_SOC5_ T6` |  | 10 |
| `0x63CE` | 22 | `STATUS_HV_BATT_HIST_SOC6_ T6` |  | 10 |
| `0x63CF` | 22 | `STATUS_HV_BATT_HIST_SOC7_ T6` |  | 10 |
| `0x63D0` | 22 | `STATUS_HV_BATT_HIST_SOC1_ T7` |  | 10 |
| `0x63D1` | 22 | `STATUS_HV_BATT_HIST_SOC2_ T7` |  | 10 |
| `0x63D2` | 22 | `STATUS_HV_BATT_HIST_SOC3_ T7` |  | 10 |
| `0x63D3` | 22 | `STATUS_HV_BATT_HIST_SOC4_ T7` |  | 10 |
| `0x63D4` | 22 | `STATUS_HV_BATT_HIST_SOC5_ T7` |  | 10 |
| `0x63D5` | 22 | `STATUS_HV_BATT_HIST_SOC6_ T7` |  | 10 |
| `0x63D6` | 22 | `STATUS_HV_BATT_HIST_SOC7_ T7` |  | 10 |
| `0x6332` | 22 | `STATUS_LADUNG_HV_BATTERIE` |  | 1 |
| `0x6333` | 22 | `STATUS_ENTLADUNG_HV_BATTERIE` |  | 1 |
| `0x6370` | 22 | `STATUS_HVB_SOC_FAHRB` |  | 14 |
| `0x6371` | 22 | `STATUS_HVBHIST_STARTSOC_0_HUB_0` |  | 12 |
| `0x6372` | 22 | `STATUS_HVBHIST_STARTSOC_0_HUB_5` |  | 12 |
| `0x6373` | 22 | `STATUS_HVBHIST_STARTSOC_0_HUB_10` |  | 12 |
| `0x6374` | 22 | `STATUS_HVBHIST_STARTSOC_0_HUB_15_ L` |  | 6 |
| `0x6375` | 22 | `STATUS_HVBHIST_STARTSOC_0_HUB_25_ L` |  | 6 |
| `0x6376` | 22 | `STATUS_HVBHIST_STARTSOC_0_HUB_35_ L` |  | 6 |
| `0x6377` | 22 | `STATUS_HVBHIST_STARTSOC_0_HUB_50_ L` |  | 6 |
| `0x6378` | 22 | `STATUS_HVBHIST_STARTSOC_20_HUB_0` |  | 12 |
| `0x6379` | 22 | `STATUS_HVBHIST_STARTSOC_20_HUB_5` |  | 12 |
| `0x637A` | 22 | `STATUS_HVBHIST_STARTSOC_20_HUB_10` |  | 12 |
| `0x637B` | 22 | `STATUS_HVBHIST_STARTSOC_20_HUB_15` |  | 12 |
| `0x637C` | 22 | `STATUS_HVBHIST_STARTSOC_20_HUB_25_L` |  | 6 |
| `0x637D` | 22 | `STATUS_HVBHIST_STARTSOC_20_HUB_35_L` |  | 6 |
| `0x637E` | 22 | `STATUS_HVBHIST_STARTSOC_20_HUB_50_L` |  | 6 |
| `0x637F` | 22 | `STATUS_HVBHIST_STARTSOC_25_HUB_0` |  | 12 |
| `0x6380` | 22 | `STATUS_HVBHIST_STARTSOC_25_HUB_5` |  | 12 |
| `0x6381` | 22 | `STATUS_HVBHIST_STARTSOC_25_HUB_10` |  | 12 |
| `0x6382` | 22 | `STATUS_HVBHIST_STARTSOC_25_HUB_15` |  | 12 |
| `0x6383` | 22 | `STATUS_HVBHIST_STARTSOC_25_HUB_25` |  | 12 |
| `0x6384` | 22 | `STATUS_HVBHIST_STARTSOC_25_HUB_35_L` |  | 6 |
| `0x6385` | 22 | `STATUS_HVBHIST_STARTSOC_25_HUB_50_L` |  | 6 |
| `0x6386` | 22 | `STATUS_HVBHIST_STARTSOC_30_HUB_0` |  | 12 |
| `0x6387` | 22 | `STATUS_HVBHIST_STARTSOC_30_HUB_5` |  | 12 |
| `0x6388` | 22 | `STATUS_HVBHIST_STARTSOC_30_HUB_10` |  | 12 |
| `0x6389` | 22 | `STATUS_HVBHIST_STARTSOC_30_HUB_15` |  | 12 |
| `0x638A` | 22 | `STATUS_HVBHIST_STARTSOC_30_HUB_25` |  | 12 |
| `0x638B` | 22 | `STATUS_HVBHIST_STARTSOC_30_HUB_35` |  | 12 |
| `0x638C` | 22 | `STATUS_HVBHIST_STARTSOC_30_HUB_50_L` |  | 6 |
| `0x638D` | 22 | `STATUS_HVBHIST_STARTSOC_50_HUB_0` |  | 12 |
| `0x638E` | 22 | `STATUS_HVBHIST_STARTSOC_50_HUB_5` |  | 12 |
| `0x638F` | 22 | `STATUS_HVBHIST_STARTSOC_50_HUB_10` |  | 12 |
| `0x6390` | 22 | `STATUS_HVBHIST_STARTSOC_50_HUB_15` |  | 12 |
| `0x6391` | 22 | `STATUS_HVBHIST_STARTSOC_50_HUB_25` |  | 12 |
| `0x6392` | 22 | `STATUS_HVBHIST_STARTSOC_50_HUB_35` |  | 12 |
| `0x6393` | 22 | `STATUS_HVBHIST_STARTSOC_50_HUB_50_EL` |  | 6 |
| `0x6394` | 22 | `STATUS_HVBHIST_STARTSOC_70_HUB_0` |  | 12 |
| `0x6395` | 22 | `STATUS_HVBHIST_STARTSOC_70_HUB_5` |  | 12 |
| `0x6396` | 22 | `STATUS_HVBHIST_STARTSOC_70_HUB_10` |  | 12 |
| `0x6397` | 22 | `STATUS_HVBHIST_STARTSOC_70_HUB_15` |  | 12 |
| `0x6398` | 22 | `STATUS_HVBHIST_STARTSOC_70_HUB_25` |  | 12 |
| `0x6399` | 22 | `STATUS_HVBHIST_STARTSOC_70_HUB_35_EL` |  | 6 |
| `0x639A` | 22 | `STATUS_HVBHIST_STARTSOC_70_HUB_50_EL` |  | 6 |
| `0x639B` | 22 | `STATUS_HVBHIST_STARTSOC_80_HUB_0` |  | 12 |
| `0x639C` | 22 | `STATUS_HVBHIST_STARTSOC_80_HUB_5` |  | 12 |
| `0x639D` | 22 | `STATUS_HVBHIST_STARTSOC_80_HUB_10` |  | 12 |
| `0x639E` | 22 | `STATUS_HVBHIST_STARTSOC_80_HUB_15` |  | 12 |
| `0x639F` | 22 | `STATUS_HVBHIST_STARTSOC_80_HUB_25_EL` |  | 6 |
| `0x63A0` | 22 | `STATUS_HVBHIST_STARTSOC_80_HUB_35_EL` |  | 6 |
| `0x63A1` | 22 | `STATUS_HVBHIST_STARTSOC_80_HUB_50_EL` |  | 6 |
| `0x6301` | 22 | `STEUERN_TEMPERATUREN_LESEN` | Read temperatures from the e-motor DCB (power stage) control board | 9 |
| `0x6300` | 22 | `STEUERN_EPSOFFSET_LESEN` | EPS offset -180.00° .. +180.00° | 1 |

## BMW ActiveE (E82, "BEV10") — SME (HV battery management (master))

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xAD61` | 31 | `ISOLATION` | Isolation test result | 2 |
| `0xDD61` | 22;2E | `SCHUETZ_FREIGABE` | Writes or reads the bit to enable or disable the contactor switch. Job is clamp-safe | 2 |
| `0xDD63` | 22 | `SCHUETZSCHALTUNGEN_ANZAHL` | Number of switchings of the contactor switch (currentless and under load) | 1 |
| `0xDD64` | 22 | `HVIL` | HVIL test result | 1 |
| `0xDD66` | 22 | `HV_SPANNUNG` | HV voltage of the DC link before the contactors | 1 |
| `0xDD68` | 22 | `HV_SPANNUNG_BERECHNET` | HV voltage calculated from the individual cells (battery voltage behind the contactors) | 1 |
| `0xDD69` | 22 | `HV_STROM` | HV electricity | 1 |
| `0xDD6F` | 22;2E | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: Closed or open / close or open | 2 |
| `0xDD73` | 22 | `CUMULATIVE_LADUNG` | Status cumulative charge | 1 |
| `0xDD74` | 22 | `CUMULATIVE_ENTLADUNG` | Status cumulative discharge | 1 |
| `0xDD76` | 22 | `STATUS_KL30C_SPANNUNG` | Voltage terminal 30C | 1 |
| `0xDD7B` | 22;2E | `REFERENZ_KAPAZITAET` | Read and adjust battery capacity | 2 |
| `0xDD7C` | 22 | `GW_INFO` | Warranty data | 26 |
| `0xDD7D` | 22 | `STROMGRENZEN` | Current limits | 2 |
| `0xDD7E` | 22 | `SPANNUNGSGRENZEN` | Voltage limits | 2 |
| `0xDD8E` | 22 | `HVB_HISTORIE_ZYKLEN` | Output of the sum of cyclizations in the respective range during charging/discharging and output of the current loads | 28 |
| `0xDD90` | 22 | `ZEIT_TEMP_HISTOGRAMM` | Time in various temperature classes and main contactor states | 20 |
| `0xDD91` | 22 | `ZEIT_SOC_KLASSE` | Time since installation in SOC classes | 10 |
| `0xDD94` | 22 | `HV_BATT_HIST_SOC_T1` | Number of cycles at temperature T < 10°C  and at different values of current and SoC | 70 |
| `0xDD95` | 22 | `HV_BATT_HIST_SOC_T2` | Number of cycles at temperature 10°C < T < 20°C and at different values of current and SoC | 70 |
| `0xDD96` | 22 | `HV_BATT_HIST_SOC_T3` | Number of cycles at temperature 20°C < T < 30°C and at different values of current and SoC. | 70 |
| `0xDD97` | 22 | `HV_BATT_HIST_SOC_T4` | Number of cycles at temperature 30°C < T < 35°C and at different values of current and SoC | 70 |
| `0xDD98` | 22 | `HV_BATT_HIST_SOC_T5` | Number of cycles at temperature 35°C < T < 40°C and at different values of current and SoC. | 70 |
| `0xDD99` | 22 | `HV_BATT_HIST_SOC_T6` | Number of cycles at temperature 40°C < T < 45°C and at different values of current and SoC | 70 |
| `0xDD9A` | 22 | `HV_BATT_HIST_SOC_T7` | Number of cycles at temperature T > 45°C and at different values of current and SoC | 70 |
| `0xDD9B` | 22 | `ZELLSPANNUNG_MODUL_9` | Currently measured cell voltages, module 9 | 12 |
| `0xDD9C` | 22 | `ZELLSPANNUNG_MODUL_10` | Currently measured cell voltages, module 10 | 12 |
| `0xDD9D` | 22 | `ZELLSPANNUNG_MODUL_11` | Currently measured cell voltages, module 11 | 12 |
| `0xDD9E` | 22 | `ZELLSPANNUNG_MODUL_12` | Currently measured cell voltages, module 12 | 12 |
| `0xDD9F` | 22 | `FAHRGESTELLNUMMER` | Current chassis number (VIN) of the vehicle in which the HV battery (storage) is installed | 1 |
| `0xDDA1` | 2E;22 | `KUEHLMITTELPUMPE` | Result values or control of the coolant pump for cooling the HV battery in % (0-100%) | 3 |
| `0xDDA2` | 22 | `TEMP_SENSOREN_BEV10` | Return the temperature values of all CSCs | 52 |
| `0xDDA3` | 22 | `ZELLSPANNUNG_MODUL_13` | Currently measured cell voltages, module 13 | 12 |
| `0xDDA5` | 2E;22 | `FREIGABE_KUEHLMITTELPUMPE` | Enable or read out status of the coolant pump (0 = not enabled, 1 = enabled) | 2 |
| `0xDDA6` | 22 | `SCHUETZ_SCHALTER_BEV10` | Status of the three contactor switches for the 3 HV batteries: transmission tunnel, front section, tank | 3 |
| `0xDDA7` | 22 | `ISOLATIONSWIDERSTAND_BEV10` | Value of all insulation resistances (all HV batteries) | 12 |
| `0xDDA8` | 22 | `CSC_IDS_BEV10` | HW numbers of all CSCs (Cell Supervisory Circuit) of the BEV2010 | 13 |
| `0xDDA9` | 22 | `KUEHLKREISLAUF_TEMP_BEV10` | Coolant circuit temperature BEV2010 | 3 |
| `0xDDAA` | 22 | `HV_SPANNUNG_BATT_BEV10` | Values for HV voltages for the BEV2010 | 14 |
| `0xDDAD` | 22 | `VARIANTE_CSCS_BEV10` | Return the CSC variant of all modules | 13 |
| `0xDDAE` | 22 | `ZELLSPANNUNG_MODUL_4` | Currently measured cell voltages, module 4 | 12 |
| `0xDDAF` | 22 | `ZELLSPANNUNG_MODUL_5` | Currently measured cell voltages, module 5 | 12 |
| `0xDDB0` | 22 | `ZELLSPANNUNG_MODUL_6` | Currently measured cell voltages, module 6 | 12 |
| `0xDDB1` | 22 | `ZELLSPANNUNG_MODUL_7` | Currently measured cell voltages, module 7 | 12 |
| `0xDDB2` | 22 | `ZELLSPANNUNG_MODUL_8` | Currently measured cell voltages, module 8 | 12 |
| `0xDDB6` | 22 | `ALTERUNG_INNENWIDERSTAND` | Resistance increase: resistance increased by x %, percentage value: (R_akt / R_neu - 1) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDB7` | 22 | `ALTERUNG_KAPAZITAET` | Remaining capacity of the battery (storage), percentage value: ( C_akt/C_nenn(neu) ) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDB9` | 22 | `ZELLSPANNUNG_MODUL_1` | Currently measured cell voltages in V, module 1 | 12 |
| `0xDDBA` | 22 | `ZELLSPANNUNG_MODUL_2` | Currently measured cell voltages, module 2 | 12 |
| `0xDDBB` | 22 | `ZELLSPANNUNG_MODUL_3` | Currently measured cell voltages in V, module 3 | 12 |
| `0xDDBC` | 22 | `ANZEIGE_SOC` | current advertisement Soc | 3 |
| `0xDDBD` | 22 | `SERVICE_DISCONNECT` | Status of the service disconnect (0 = open, 1 = closed) | 1 |
| `0xDDBE` | 22 | `VORLADUNG` | Info about time, current and temperatures during pre-charging | 15 |
| `0xDDBF` | 22 | `ZELLSPANNUNGEN_MIN_MAX` | minimum and maximum single cell voltages are output | 2 |
| `0xDDC0` | 22 | `TEMPSENSOREN_MIN_MAX` | Output of the minimum and maximum temperature values of all individual cells | 2 |
| `0xDDC2` | 22 | `ALTERUNG_PARAMETER` | Aging values of the series/parallel ohmic resistance and the parallel capacitance | 6 |
| `0xDDC4` | 22 | `SOC` | Read out SOC value (in%) and plausibility or specification of the SOC value (0-100%) | 2 |
| `0xDDC6` | 22 | `HISTO_SYM_DAUER` | Read the number of cell balancing events in the respective time classes (target time during which the balancing resistors are to be switched active). | 8 |
| `0xDDC8` | 22 | `SYM_DELTASOC` | Maximum SoC difference in% over the entire HVS. Ring memory of the last 5 trips | 5 |
| `0xDDCA` | 22 | `SERIENNUMMER_ECU` | Serial number SME ECU | 1 |
| `0xF190` | 22 | `VIN` | Chassis number | 1 |
| `0x6500` | 2E | `_SOC_GRENZEN` | State of charge limit values | 2 |
| `0x6501` | 2E | `_ISOLATION` | Insulation monitoring | 2 |
| `0x6502` | 2E | `_UEBERLAST_SCHWELLE` | Charge and discharge current limits | 2 |
| `0x6503` | 2E | `_KURZSCHLUSS_STROMGRENZE` | Short circuit current limit | 2 |
| `0x6504` | 2E | `_LADE_SPANNUNGSGRENZE` | Load voltage limit | 2 |
| `0x6506` | 2E | `_SCHUETZ_K1` | K1 contactor | 2 |
| `0x6507` | 2E | `_SCHUETZ_K2` | K2 contactor | 2 |
| `0x6508` | 2E | `_SCHUETZ_K3` | K3 contactor | 2 |
| `0x6509` | 2E | `_SERIENNUMMER` | HV battery (storage) serial number | 2 |
| `0x650B` | 2E | `_ENTLADE_SPANNUNGSGRENZE` | Discharge voltage limit | 2 |
| `0x650C` | 2E | `_SCHUETZ_K4` | K4 contactor | 2 |
| `0x650D` | 2E | `_SCHUETZ_K5` | K5 contactor | 2 |
| `0x650E` | 2E | `_SCHUETZ_K6` | K6 contactor | 2 |
| `0x650F` | 2E | `_SCHUETZ_K7` | K7 contactor | 2 |
| `0x6514` | 2E | `_FUSI_ENTPRELLZEITEN` | Increase debounce times for FuSi level 2 (functional safety) functions | 2 |
| `0x6518` | 2E | `_CSC_INDIZIERUNG_BEV_10` | CSC indexing for BEV-10 | 2 |
| `0x6519` | 2E | `_CSC_STANDBY` | Put CSCs in standby mode | 2 |
| `0x651B` | 2E | `_ANFORDERUNG_SCHUETZE_SCHLIESSEN` | Close contactor | 2 |

## BMW ActiveE (E82, "BEV10") — SMES1 (HV battery management slave 1)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x6500` | 2E | `_SOC_GRENZEN` | State of charge limit values | 2 |
| `0x6501` | 2E | `_ISOLATION` | Insulation monitoring | 2 |
| `0x6502` | 2E | `_UEBERLAST_SCHWELLE` | Charge and discharge current limits | 2 |
| `0x6503` | 2E | `_KURZSCHLUSS_STROMGRENZE` | Short circuit current limit | 2 |
| `0x6504` | 2E | `_LADE_SPANNUNGSGRENZE` | Load voltage limit | 2 |
| `0x6506` | 2E | `_SCHUETZ_K1` | K1 contactor | 2 |
| `0x6507` | 2E | `_SCHUETZ_K2` | K2 contactor | 2 |
| `0x6508` | 2E | `_SCHUETZ_K3` | K3 contactor | 2 |
| `0x6509` | 2E | `_SERIENNUMMER` | HV battery (storage) serial number | 2 |
| `0x650B` | 2E | `_ENTLADE_SPANNUNGSGRENZE` | Discharge voltage limit | 2 |
| `0x650C` | 2E | `_SCHUETZ_K4` | K4 contactor | 2 |
| `0x650D` | 2E | `_SCHUETZ_K5` | K5 contactor | 2 |
| `0x650E` | 2E | `_SCHUETZ_K6` | K6 contactor | 2 |
| `0x650F` | 2E | `_SCHUETZ_K7` | K7 contactor | 2 |
| `0x6511` | 2E | `_SYM_MODUS` | Symmetry mode of the SEM | 2 |
| `0x6512` | 2E | `_MESSBOTSCHAFTEN` | Switch measurement messages on / off | 2 |
| `0x6514` | 2E | `_FUSI_ENTPRELLZEITEN` | Increase debounce times for FuSi level 2 (functional safety) functions | 2 |
| `0x6516` | 22 | `_ST_SYM_MODUS` | Status of the SME cell balancing mode | 1 |
| `0x6518` | 2E | `_CSC_INDIZIERUNG_BEV_10` | CSC indexing for BEV-10 | 1 |
| `0x6519` | 2E | `_CSC_STANDBY` | Put CSCs in standby mode | 2 |
| `0x651B` | 2E | `_ANFORDERUNG_SCHUETZE_SCHLIESSEN` | Close contactor | 2 |
| `0xAD61` | 31 | `ISOLATION` | Isolation test result | 2 |
| `0xDD61` | 2E;22 | `SCHUETZ_FREIGABE` | Writes or reads the bit to enable or disable the contactor switch. Job is clamp-safe | 2 |
| `0xDD62` | 22 | `HV_STROM_MAX` | Maximum HV current | 2 |
| `0xDD63` | 22 | `SCHUETZSCHALTUNGEN_ANZAHL` | Number of switchings of the contactor switch (currentless and under load) | 1 |
| `0xDD64` | 22 | `HVIL` | Disturb/disable the interlock generator in the BMS / HVIL test result | 1 |
| `0xDD65` | 22 | `SOC_MIN_MAX` | Min/max values of the SOC | 2 |
| `0xDD66` | 22 | `HV_SPANNUNG` | HV voltage of the DC link before the contactors | 1 |
| `0xDD67` | 22 | `ANZAHL_KUEHLANFORDERUNG_DRINGEND` | Counter describing how often a higher temperature state was reached in consecutive terminal cycles. (Maximum value) | 1 |
| `0xDD68` | 22 | `HV_SPANNUNG_BERECHNET` | HV voltage calculated from the individual cells (battery voltage behind the contactors) | 1 |
| `0xDD69` | 22 | `HV_STROM` | HV electricity | 1 |
| `0xDD6F` | 2E;22 | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: Closed or open / close or open | 2 |
| `0xDD72` | 22 | `AUFSTART_VERHINDERER` | Reason for not starting the HV system | 1 |
| `0xDD73` | 22 | `CUMULATIVE_LADUNG` | Status cumulative charge | 1 |
| `0xDD74` | 22 | `CUMULATIVE_ENTLADUNG` | Status cumulative discharge | 1 |
| `0xDD76` | 22 | `STATUS_KL30C_SPANNUNG` | Voltage terminal 30C | 1 |
| `0xDD7B` | 22;2E | `REFERENZ_KAPAZITAET` | Read and adjust battery capacity | 2 |
| `0xDD7C` | 22 | `GW_INFO` | Warranty data | 26 |
| `0xDD7D` | 22 | `STROMGRENZEN` | Current limits | 2 |
| `0xDD7E` | 22 | `SPANNUNGSGRENZEN` | Voltage limits | 2 |
| `0xDD8E` | 22 | `HVB_HISTORIE_ZYKLEN` | Output of the sum of cyclizations in the respective range during charging/discharging and output of the current loads | 28 |
| `0xDD90` | 22 | `ZEIT_TEMP_HISTOGRAMM` | Time in various temperature classes and main contactor states | 20 |
| `0xDD91` | 22 | `ZEIT_SOC_KLASSE` | Time since installation in SOC classes | 10 |
| `0xDD92` | 22 | `HVB_HISTORIE_MIN_SOC` | History, state of charge, minimum value of the last five days | 6 |
| `0xDD93` | 22 | `HVB_HISTORIE_MAX_SOC` | History, state of charge, maximum value of the last five days | 6 |
| `0xDD94` | 22 | `HV_BATT_HIST_SOC_T1` | Number of cycles at temperature < 0°C  and at different values of current and SoC | 70 |
| `0xDD95` | 22 | `HV_BATT_HIST_SOC_T2` | Number of cycles at temperature 0°C < T < 10°C and at different values of current and SoC | 70 |
| `0xDD96` | 22 | `HV_BATT_HIST_SOC_T3` | Number of cycles at temperature 10°C < T < 20°C and at different values of current and SoC. | 70 |
| `0xDD97` | 22 | `HV_BATT_HIST_SOC_T4` | Number of cycles at temperature 20°C < T < 30°C and at different values of current and SoC | 70 |
| `0xDD98` | 22 | `HV_BATT_HIST_SOC_T5` | Number of cycles at temperature 30°C < T < 40°C and at different values of current and SoC. | 70 |
| `0xDD99` | 22 | `HV_BATT_HIST_SOC_T6` | Number of cycles at temperature 40°C < T < 50°C and at different values of current and SoC | 70 |
| `0xDD9A` | 22 | `HV_BATT_HIST_SOC_T7` | Values for histogram of the HV battery in the temperature range above 50°C | 70 |
| `0xDD9B` | 22 | `ZELLSPANNUNG_MODUL_9` | Currently measured cell voltages, module 9 | 12 |
| `0xDD9C` | 22 | `ZELLSPANNUNG_MODUL_10` | Currently measured cell voltages, module 10 | 12 |
| `0xDD9D` | 22 | `ZELLSPANNUNG_MODUL_11` | Currently measured cell voltages, module 11 | 12 |
| `0xDD9E` | 22 | `ZELLSPANNUNG_MODUL_12` | Currently measured cell voltages, module 12 | 12 |
| `0xDD9F` | 22 | `FAHRGESTELLNUMMER` | Current chassis number (VIN) of the vehicle in which the HV battery (storage) is installed | 1 |
| `0xDDA1` | 22;2E | `KUEHLMITTELPUMPE` | Result values or control of the coolant pump for cooling the HV battery in % (0-100%) | 3 |
| `0xDDA2` | 22 | `TEMP_SENSOREN_BEV10` | Return the temperature values of all CSCs | 52 |
| `0xDDA3` | 22 | `ZELLSPANNUNG_MODUL_13` | Currently measured cell voltages, module 13 | 12 |
| `0xDDA5` | 2E;22 | `FREIGABE_KUEHLMITTELPUMPE` | Enable or read out status of the coolant pump (0 = not enabled, 1 = enabled) | 2 |
| `0xDDA6` | 22 | `SCHUETZ_SCHALTER_BEV10` | Status of the three contactor switches for the 3 HV batteries: transmission tunnel, front section, tank | 3 |
| `0xDDA7` | 22 | `ISOLATIONSWIDERSTAND_BEV10` | Value of all insulation resistances (all HV batteries) | 12 |
| `0xDDA8` | 22 | `CSC_IDS_BEV10` | HW numbers of all CSCs (Cell Supervisory Circuit) of the BEV2010 | 13 |
| `0xDDA9` | 22 | `KUEHLKREISLAUF_TEMP_BEV10` | Coolant circuit temperature BEV2010 | 3 |
| `0xDDAA` | 22 | `HV_SPANNUNG_BATT_BEV10` | Values for HV voltages for the BEV2010 | 14 |
| `0xDDAD` | 22 | `VARIANTE_CSCS_BEV10` | Return the CSC variant of all modules | 13 |
| `0xDDAE` | 22 | `ZELLSPANNUNG_MODUL_4` | Currently measured cell voltages, module 4 | 12 |
| `0xDDAF` | 22 | `ZELLSPANNUNG_MODUL_5` | Currently measured cell voltages, module 5 | 12 |
| `0xDDB0` | 22 | `ZELLSPANNUNG_MODUL_6` | Currently measured cell voltages, module 6 | 12 |
| `0xDDB1` | 22 | `ZELLSPANNUNG_MODUL_7` | Currently measured cell voltages, module 7 | 12 |
| `0xDDB2` | 22 | `ZELLSPANNUNG_MODUL_8` | Currently measured cell voltages, module 8 | 12 |
| `0xDDB6` | 22 | `ALTERUNG_INNENWIDERSTAND` | Resistance increase: resistance increased by x %, percentage value: (R_akt / R_neu - 1) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDB7` | 22 | `ALTERUNG_KAPAZITAET` | Remaining capacity of the battery (storage), percentage value: ( C_akt/C_nenn(neu) ) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDB9` | 22 | `ZELLSPANNUNG_MODUL_1` | Currently measured cell voltages in V, module 1 | 12 |
| `0xDDBA` | 22 | `ZELLSPANNUNG_MODUL_2` | Currently measured cell voltages, module 2 | 12 |
| `0xDDBB` | 22 | `ZELLSPANNUNG_MODUL_3` | Currently measured cell voltages in V, module 3 | 12 |
| `0xDDBC` | 22 | `ANZEIGE_SOC` | current advertisement Soc | 3 |
| `0xDDBD` | 22 | `SERVICE_DISCONNECT` | Status of the service disconnect (0 = open, 1 = closed) | 1 |
| `0xDDBE` | 22 | `ZEIT_VORLADUNG` | Last required precharge time (ring buffer) | 15 |
| `0xDDBF` | 22 | `ZELLSPANNUNGEN_MIN_MAX` | minimum and maximum single cell voltages are output | 2 |
| `0xDDC0` | 22 | `TEMPSENSOREN_MIN_MAX` | Output of the minimum and maximum temperature values of all individual cells | 2 |
| `0xDDC2` | 22 | `ALTERUNG_PARAMETER` | Aging values of the series/parallel ohmic resistance and the parallel capacitance | 6 |
| `0xDDC4` | 22 | `SOC` | Return SOC value (in %) and plausibility | 2 |
| `0xDDC6` | 22 | `HISTO_SYM_DAUER` | Read the number of cell balancing events in the respective time classes (target time during which the balancing resistors are to be switched active). | 8 |
| `0xDDC7` | 22 | `HISTO_SYM_ZELLANZAHL` | Read the number of sleep events in which the respective cell count was commanded for cell balancing. | 8 |
| `0xDDC8` | 22 | `SYM_DELTASOC` | Maximum SoC difference in% over the entire HVS. Ring memory of the last 5 trips | 5 |
| `0xDDC9` | 22 | `MAX_SYM_DAUER` | Maximum cell-balancing duration of the last successful balancing operations | 10 |
| `0xDDCA` | 22 | `SERIENNUMMER_ECU` | Serial number SME ECU | 1 |

## BMW ActiveE (E82, "BEV10") — SMES2 (HV battery management slave 2)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0x6500` | 2E | `_SOC_GRENZEN` | State of charge limit values | 2 |
| `0x6501` | 2E | `_ISOLATION` | Insulation monitoring | 2 |
| `0x6502` | 2E | `_UEBERLAST_SCHWELLE` | Charge and discharge current limits | 2 |
| `0x6503` | 2E | `_KURZSCHLUSS_STROMGRENZE` | Short circuit current limit | 2 |
| `0x6504` | 2E | `_LADE_SPANNUNGSGRENZE` | Load voltage limit | 2 |
| `0x6506` | 2E | `_SCHUETZ_K1` | K1 contactor | 2 |
| `0x6507` | 2E | `_SCHUETZ_K2` | K2 contactor | 2 |
| `0x6508` | 2E | `_SCHUETZ_K3` | K3 contactor | 2 |
| `0x6509` | 2E | `_SERIENNUMMER` | HV battery (storage) serial number | 2 |
| `0x650B` | 2E | `_ENTLADE_SPANNUNGSGRENZE` | Discharge voltage limit | 2 |
| `0x650C` | 2E | `_SCHUETZ_K4` | K4 contactor | 2 |
| `0x650D` | 2E | `_SCHUETZ_K5` | K5 contactor | 2 |
| `0x650E` | 2E | `_SCHUETZ_K6` | K6 contactor | 2 |
| `0x650F` | 2E | `_SCHUETZ_K7` | K7 contactor | 2 |
| `0x6511` | 2E | `_SYM_MODUS` | Symmetry mode of the SEM | 2 |
| `0x6512` | 2E | `_MESSBOTSCHAFTEN` | Switch measurement messages on / off | 2 |
| `0x6514` | 2E | `_FUSI_ENTPRELLZEITEN` | Increase debounce times for FuSi level 2 (functional safety) functions | 2 |
| `0x6516` | 22 | `_ST_SYM_MODUS` | Status of the SME cell balancing mode | 1 |
| `0x6518` | 2E | `_CSC_INDIZIERUNG_BEV_10` | CSC indexing for BEV-10 | 1 |
| `0x6519` | 2E | `_CSC_STANDBY` | Put CSCs in standby mode | 2 |
| `0x651B` | 2E | `_ANFORDERUNG_SCHUETZE_SCHLIESSEN` | Close contactor | 2 |
| `0xAD61` | 31 | `ISOLATION` | Isolation test result | 2 |
| `0xDD61` | 2E;22 | `SCHUETZ_FREIGABE` | Writes or reads the bit to enable or disable the contactor switch. Job is clamp-safe | 2 |
| `0xDD62` | 22 | `HV_STROM_MAX` | Maximum HV current | 2 |
| `0xDD63` | 22 | `SCHUETZSCHALTUNGEN_ANZAHL` | Number of switchings of the contactor switch (currentless and under load) | 1 |
| `0xDD64` | 22 | `HVIL` | Disturb/disable the interlock generator in the BMS / HVIL test result | 1 |
| `0xDD65` | 22 | `SOC_MIN_MAX` | Min/max values of the SOC | 2 |
| `0xDD66` | 22 | `HV_SPANNUNG` | HV voltage of the DC link before the contactors | 1 |
| `0xDD67` | 22 | `ANZAHL_KUEHLANFORDERUNG_DRINGEND` | Counter describing how often a higher temperature state was reached in consecutive terminal cycles. (Maximum value) | 1 |
| `0xDD68` | 22 | `HV_SPANNUNG_BERECHNET` | HV voltage calculated from the individual cells (battery voltage behind the contactors) | 1 |
| `0xDD69` | 22 | `HV_STROM` | HV electricity | 1 |
| `0xDD6F` | 2E;22 | `KUEHLKREISLAUF_VENTIL` | Status / control coolant valve: Closed or open / close or open | 2 |
| `0xDD72` | 22 | `AUFSTART_VERHINDERER` | Reason for not starting the HV system | 1 |
| `0xDD73` | 22 | `CUMULATIVE_LADUNG` | Status cumulative charge | 1 |
| `0xDD74` | 22 | `CUMULATIVE_ENTLADUNG` | Status cumulative discharge | 1 |
| `0xDD76` | 22 | `STATUS_KL30C_SPANNUNG` | Voltage terminal 30C | 1 |
| `0xDD7B` | 22;2E | `REFERENZ_KAPAZITAET` | Read and adjust battery capacity | 2 |
| `0xDD7C` | 22 | `GW_INFO` | Warranty data | 26 |
| `0xDD7D` | 22 | `STROMGRENZEN` | Current limits | 2 |
| `0xDD7E` | 22 | `SPANNUNGSGRENZEN` | Voltage limits | 2 |
| `0xDD8E` | 22 | `HVB_HISTORIE_ZYKLEN` | Output of the sum of cyclizations in the respective range during charging/discharging and output of the current loads | 28 |
| `0xDD90` | 22 | `ZEIT_TEMP_HISTOGRAMM` | Time in various temperature classes and main contactor states | 20 |
| `0xDD91` | 22 | `ZEIT_SOC_KLASSE` | Time since installation in SOC classes | 10 |
| `0xDD92` | 22 | `HVB_HISTORIE_MIN_SOC` | History, state of charge, minimum value of the last five days | 6 |
| `0xDD93` | 22 | `HVB_HISTORIE_MAX_SOC` | History, state of charge, maximum value of the last five days | 6 |
| `0xDD94` | 22 | `HV_BATT_HIST_SOC_T1` | Number of cycles at temperature < 0°C  and at different values of current and SoC | 70 |
| `0xDD95` | 22 | `HV_BATT_HIST_SOC_T2` | Number of cycles at temperature 0°C < T < 10°C and at different values of current and SoC | 70 |
| `0xDD96` | 22 | `HV_BATT_HIST_SOC_T3` | Number of cycles at temperature 10°C < T < 20°C and at different values of current and SoC. | 70 |
| `0xDD97` | 22 | `HV_BATT_HIST_SOC_T4` | Number of cycles at temperature 20°C < T < 30°C and at different values of current and SoC | 70 |
| `0xDD98` | 22 | `HV_BATT_HIST_SOC_T5` | Number of cycles at temperature 30°C < T < 40°C and at different values of current and SoC. | 70 |
| `0xDD99` | 22 | `HV_BATT_HIST_SOC_T6` | Number of cycles at temperature 40°C < T < 50°C and at different values of current and SoC | 70 |
| `0xDD9A` | 22 | `HV_BATT_HIST_SOC_T7` | Values for histogram of the HV battery in the temperature range above 50°C | 70 |
| `0xDD9B` | 22 | `ZELLSPANNUNG_MODUL_9` | Currently measured cell voltages, module 9 | 12 |
| `0xDD9C` | 22 | `ZELLSPANNUNG_MODUL_10` | Currently measured cell voltages, module 10 | 12 |
| `0xDD9D` | 22 | `ZELLSPANNUNG_MODUL_11` | Currently measured cell voltages, module 11 | 12 |
| `0xDD9E` | 22 | `ZELLSPANNUNG_MODUL_12` | Currently measured cell voltages, module 12 | 12 |
| `0xDD9F` | 22 | `FAHRGESTELLNUMMER` | Current chassis number (VIN) of the vehicle in which the HV battery (storage) is installed | 1 |
| `0xDDA1` | 22;2E | `KUEHLMITTELPUMPE` | Result values or control of the coolant pump for cooling the HV battery in % (0-100%) | 3 |
| `0xDDA2` | 22 | `TEMP_SENSOREN_BEV10` | Return the temperature values of all CSCs | 52 |
| `0xDDA3` | 22 | `ZELLSPANNUNG_MODUL_13` | Currently measured cell voltages, module 13 | 12 |
| `0xDDA5` | 2E;22 | `FREIGABE_KUEHLMITTELPUMPE` | Enable or read out status of the coolant pump (0 = not enabled, 1 = enabled) | 2 |
| `0xDDA6` | 22 | `SCHUETZ_SCHALTER_BEV10` | Status of the three contactor switches for the 3 HV batteries: transmission tunnel, front section, tank | 3 |
| `0xDDA7` | 22 | `ISOLATIONSWIDERSTAND_BEV10` | Value of all insulation resistances (all HV batteries) | 12 |
| `0xDDA8` | 22 | `CSC_IDS_BEV10` | HW numbers of all CSCs (Cell Supervisory Circuit) of the BEV2010 | 13 |
| `0xDDA9` | 22 | `KUEHLKREISLAUF_TEMP_BEV10` | Coolant circuit temperature BEV2010 | 3 |
| `0xDDAA` | 22 | `HV_SPANNUNG_BATT_BEV10` | Values for HV voltages for the BEV2010 | 14 |
| `0xDDAD` | 22 | `VARIANTE_CSCS_BEV10` | Return the CSC variant of all modules | 13 |
| `0xDDAE` | 22 | `ZELLSPANNUNG_MODUL_4` | Currently measured cell voltages, module 4 | 12 |
| `0xDDAF` | 22 | `ZELLSPANNUNG_MODUL_5` | Currently measured cell voltages, module 5 | 12 |
| `0xDDB0` | 22 | `ZELLSPANNUNG_MODUL_6` | Currently measured cell voltages, module 6 | 12 |
| `0xDDB1` | 22 | `ZELLSPANNUNG_MODUL_7` | Currently measured cell voltages, module 7 | 12 |
| `0xDDB2` | 22 | `ZELLSPANNUNG_MODUL_8` | Currently measured cell voltages, module 8 | 12 |
| `0xDDB6` | 22 | `ALTERUNG_INNENWIDERSTAND` | Resistance increase: resistance increased by x %, percentage value: (R_akt / R_neu - 1) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDB7` | 22 | `ALTERUNG_KAPAZITAET` | Remaining capacity of the battery (storage), percentage value: ( C_akt/C_nenn(neu) ) * 100, 0 = end of life reached, 100 = new condition | 1 |
| `0xDDB9` | 22 | `ZELLSPANNUNG_MODUL_1` | Currently measured cell voltages in V, module 1 | 12 |
| `0xDDBA` | 22 | `ZELLSPANNUNG_MODUL_2` | Currently measured cell voltages, module 2 | 12 |
| `0xDDBB` | 22 | `ZELLSPANNUNG_MODUL_3` | Currently measured cell voltages in V, module 3 | 12 |
| `0xDDBC` | 22 | `ANZEIGE_SOC` | current advertisement Soc | 3 |
| `0xDDBD` | 22 | `SERVICE_DISCONNECT` | Status of the service disconnect (0 = open, 1 = closed) | 1 |
| `0xDDBE` | 22 | `ZEIT_VORLADUNG` | Last required precharge time (ring buffer) | 15 |
| `0xDDBF` | 22 | `ZELLSPANNUNGEN_MIN_MAX` | minimum and maximum single cell voltages are output | 2 |
| `0xDDC0` | 22 | `TEMPSENSOREN_MIN_MAX` | Output of the minimum and maximum temperature values of all individual cells | 2 |
| `0xDDC2` | 22 | `ALTERUNG_PARAMETER` | Aging values of the series/parallel ohmic resistance and the parallel capacitance | 6 |
| `0xDDC4` | 22 | `SOC` | Return SOC value (in %) and plausibility | 2 |
| `0xDDC6` | 22 | `HISTO_SYM_DAUER` | Read the number of cell balancing events in the respective time classes (target time during which the balancing resistors are to be switched active). | 8 |
| `0xDDC7` | 22 | `HISTO_SYM_ZELLANZAHL` | Read the number of sleep events in which the respective cell count was commanded for cell balancing. | 8 |
| `0xDDC8` | 22 | `SYM_DELTASOC` | Maximum SoC difference in% over the entire HVS. Ring memory of the last 5 trips | 5 |
| `0xDDC9` | 22 | `MAX_SYM_DAUER` | Maximum cell-balancing duration of the last successful balancing operations | 10 |
| `0xDDCA` | 22 | `SERIENNUMMER_ECU` | Serial number SME ECU | 1 |

## BMW ActiveE (E82, "BEV10") — KLE (On-board charger)

| DID | Svc | Job argument | Description | Fields |
|---|---|---|---|---:|
| `0xDF20` | 22 | `BETRIEBSART_AKTUELL` | Status of the current operating mode of the charger electronics | 1 |
| `0xDF21` | 22 | `FEHLERZUSTAENDE` | Fault states of the charging electronics | 1 |
| `0xDF22` | 22 | `URSACHE_DERATING` | Derating status (cause and value of the degradation) | 1 |
| `0xDF23` | 22 | `WIRKUNGSGRAD` | Efficiency status | 1 |
| `0xDF24` | 22 | `WIRKUNGSGRAD_LADEZYKLUS` | Charge cycle efficiency status | 1 |
| `0xDF25` | 22 | `AC_PHASENANZAHL` | Status of the number of AC phases | 1 |
| `0xDF26` | 22 | `NETZFREQUENZ` | Mains frequency status per phase | 1 |
| `0xDF27` | 22 | `LADEDAUER` | Charge duration status | 1 |
| `0xDF28` | 22 | `TEMPERATUR_LADEELEKTRONIK` | Current temperature of charging electronics | 1 |
| `0xDF29` | 22 | `SME_BEGRENZUNGSGROESSEN` | Charging power limitation values from SME | 2 |
| `0xDF2A` | 22 | `URSACHE_LADEUNTERBRECHUNG` | Charge inhibitor status, charger electronics | 1 |
| `0xDF2B` | 22 | `CHARGE_ENABLE_HW` | Status charge enable HW line | 1 |
| `0xDF2C` | 22 | `PILOT_SIGNAL` | Pilot signal status | 1 |
| `0xDF2D` | 22 | `PROXIMITY_SIGNAL` | Proximity status | 2 |
| `0xDF2E` | 22 | `HVDC_LEISTUNG` | Status HV DC power of the charger electronics | 1 |
| `0xDF2F` | 22 | `HVDC_LEISTUNG_MAX` | Status maximum HV DC power of the charger electronics | 1 |
| `0xDF30` | 22 | `AC_WIRKLEISTUNG_LADEZYKLUS` | Status of active power drawn from the mains, current charge cycle | 1 |
| `0xDF31` | 22 | `AC_SPANNUNG_EFFEKTIV` | Status RMS values of the AC phase voltages per phase | 1 |
| `0xDF32` | 22 | `HVDC_SPANNUNG` | HV DC voltage at the charging electronics | 1 |
| `0xDF33` | 22 | `HVDC_SPANNUNG_MAX` | Maximum HV DC voltage at the charging electronics | 1 |
| `0xDF34` | 22 | `HVDC_STROM` | Status HV DC current of the charger electronics | 1 |
| `0xDF35` | 22 | `HVDC_STROM_MAX` | Status maximum HV DC current of the charger electronics | 1 |
| `0xDF36` | 22 | `AC_STROM_EFFEKTIV_LEITER` | Status RMS values of the AC phase currents per phase | 1 |
| `0xDF37` | 22 | `AC_STROM_MAX` | Status maximum AC current of the charger electronics | 1 |
| `0xDF38` | 22 | `KL30_SPANNUNG` | Current voltage at terminal 30 of the charging electronics | 1 |
| `0xDF39` | 2E;22 | `ABS_MAX_DC_STROM` | Absolute measured maximum DC current | 4 |
| `0xDF3A` | 22;2E | `ABS_MAX_AC_CURRENT` | Absolute measured maximum AC current | 4 |
| `0xDF3B` | 22;2E | `ABS_MIN_MAX_TEMPERATUR` | Absolute measured maximum and minimum temperature | 3 |
| `0xDF3D` | 22 | `SOFTWAREVERSION_LADEELEKTRONIK` | SW version of the charger electronics | 1 |
| `0xDF3F` | 22 | `DIGITAL_IN_OUT` | Values of the digital inputs and outputs of the charger electronics | 1 |
| `0xDF43` | 22 | `PROXIMITY_PIN` | Voltage and information about the connection of the proximity pin | 2 |
| `0xDF44` | 22 | `PILOT_HW` | Information on frequency, duty cycle, and voltage of the pilot pin | 4 |
