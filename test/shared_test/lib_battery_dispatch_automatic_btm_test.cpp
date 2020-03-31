#include "lib_battery_dispatch_automatic_btm_test.h"

TEST_F(AutoBTMTest_lib_battery_dispatch, DispatchAutoBTMGridCharging) {
    double dtHour = 1;
    CreateBattery(dtHour);

    dispatchAutoBTM = new dispatch_automatic_behind_the_meter_t(batteryModel, dtHour, SOC_min, SOC_max, currentChoice, currentChargeMax,
        currentDischargeMax, powerChargeMax, powerDischargeMax, powerChargeMax, powerDischargeMax, 0, dispatch_t::BTM_MODES::LOOK_AHEAD, 0, 1, 24, 1, true, true, false, false);

    // Setup pv and load signal for peak shaving algorithm
    for (size_t h = 0; h < 24; h++) {
        pv_prediction.push_back(0); // Set detailed PV later
        if (h < 4) {
            load_prediction.push_back(600);
        }
        else {
            load_prediction.push_back(0);
        }
    }
    
    // Set detailed PV
    pv_prediction[0] = 500; pv_prediction[1] = 400; pv_prediction[2] = 300; pv_prediction[3] = 200;
    dispatchAutoBTM->update_load_data(load_prediction);
    dispatchAutoBTM->update_pv_data(pv_prediction);

    batteryPower = dispatchAutoBTM->getBatteryPower();
    batteryPower->connectionMode = ChargeController::AC_CONNECTED;

    EXPECT_EQ(batteryPower->powerBatteryChargeMaxAC, 50);

    // TEST 1: Verify no grid charging since disallowed  (_P_battery_use target is ~ -50)
    dispatchAutoBTM->update_dispatch(0, 0, 0);

    dispatchAutoBTM->dispatch(0, 0, 0);     // original target for battery power is
    EXPECT_EQ(batteryPower->powerGridToBattery, 0);
    EXPECT_NEAR(batteryPower->powerBatteryDC, 0, 0.02);

    // TEST 2: Now, allow grid charging, should charge up to Max Charge Power (enforced by restrict_power)
    batteryPower->canGridCharge = true;
    dispatchAutoBTM->update_dispatch(0, 0, 0);
    dispatchAutoBTM->dispatch(0, 0, 0);
    EXPECT_NEAR(batteryPower->powerGridToBattery, 50, 1);
    EXPECT_NEAR(batteryPower->powerBatteryDC, -48, 1);
}

TEST_F(AutoBTMTest_lib_battery_dispatch, DispatchAutoBTMPVCharging) {
    double dtHour = 1;
    CreateBattery(dtHour);

    dispatchAutoBTM = new dispatch_automatic_behind_the_meter_t(batteryModel, dtHour, SOC_min, SOC_max, currentChoice, currentChargeMax,
        currentDischargeMax, powerChargeMax, powerDischargeMax, powerChargeMax, powerDischargeMax, 0, dispatch_t::BTM_MODES::LOOK_AHEAD, 0, 1, 24, 1, true, true, false, false);

    // Setup pv and load signal for peak shaving algorithm
    for (size_t h = 0; h < 24; h++) {
        if (h > 6 && h < 18) {
            pv_prediction.push_back(700);
        }
        else {
            pv_prediction.push_back(0);
        }
        load_prediction.push_back(500);
    }

    dispatchAutoBTM->update_load_data(load_prediction);
    dispatchAutoBTM->update_pv_data(pv_prediction);

    batteryPower = dispatchAutoBTM->getBatteryPower();
    batteryPower->connectionMode = ChargeController::AC_CONNECTED;

    // Load never peaks above average load, so battery never discharges
    std::vector<double> expectedPower = { 0, 0, 0, 0, 0, 0, 0, -50, -50, -50, -50, -50, -18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (size_t h = 0; h < 24; h++) {
        if (h > 6 && h < 18) {
            batteryPower->powerPV = 700; // Match the predicted PV
        }
        else {
            batteryPower->powerPV = 0;
        }
        batteryPower->powerLoad = 500; // Match the predicted load
        dispatchAutoBTM->dispatch(0, h, 0);  
        EXPECT_NEAR(batteryPower->powerBatteryDC, expectedPower[h], 0.2) << " error in expected at hour " << h;
    }
}

TEST_F(AutoBTMTest_lib_battery_dispatch, DispatchAutoBTMPVChargeAndDischarge) {
    double dtHour = 1;
    CreateBattery(dtHour);

    dispatchAutoBTM = new dispatch_automatic_behind_the_meter_t(batteryModel, dtHour, SOC_min, SOC_max, currentChoice, currentChargeMax,
        currentDischargeMax, powerChargeMax, powerDischargeMax, powerChargeMax, powerDischargeMax, 0, dispatch_t::BTM_MODES::LOOK_AHEAD, 0, 1, 24, 1, true, true, false, false);

    // Setup pv and load signal for peak shaving algorithm
    for (size_t h = 0; h < 24; h++) {
        if (h > 6 && h < 18) {
            pv_prediction.push_back(700);
        }
        else {
            pv_prediction.push_back(0);
        }

        if (h > 18) {
            load_prediction.push_back(600);
        }
        else {
            load_prediction.push_back(500);
        }
    }

    dispatchAutoBTM->update_load_data(load_prediction);
    dispatchAutoBTM->update_pv_data(pv_prediction);

    batteryPower = dispatchAutoBTM->getBatteryPower();
    batteryPower->connectionMode = ChargeController::AC_CONNECTED;

    // Battery will charge when PV is available, then discharge when load increases at 7 pm
    std::vector<double> expectedPower = { 0, 0, 0, 0, 0, 0, 0, -50, -50, -50, -50, -50, -18, 0, 0, 0, 0, 0, 0, 50, 50, 50, 50, 50, 50, 50, 50 };
    for (size_t h = 0; h < 24; h++) {
        batteryPower->powerLoad = 500;
        batteryPower->powerPV = 0;
        if (h > 6 && h < 18) {
            batteryPower->powerPV = 700; // Match the predicted PV
        }
        else if (h > 18) {
            batteryPower->powerLoad = 600; // Match the predicted load
        }
        dispatchAutoBTM->dispatch(0, h, 0);
        EXPECT_NEAR(batteryPower->powerBatteryDC, expectedPower[h], 0.2) << " error in expected at hour " << h;
    }
}

TEST_F(AutoBTMTest_lib_battery_dispatch, DispatchAutoBTMPVChargeAndDischargeSubhourly) {
    double dtHour = 0.25;
    CreateBattery(dtHour);

    dispatchAutoBTM = new dispatch_automatic_behind_the_meter_t(batteryModel, dtHour, SOC_min, SOC_max, currentChoice, currentChargeMax,
        currentDischargeMax, powerChargeMax, powerDischargeMax, powerChargeMax, powerDischargeMax, 0, dispatch_t::BTM_MODES::LOOK_AHEAD, 0, 1, 24, 1, true, true, false, false);
    
    std::vector<double> expectedPower;
    // Setup pv and load signal for peak shaving algorithm
    for (size_t h = 0; h < 24; h++) {
        for (size_t step = 0; step < 4; step++) {
            if (h > 6 && h < 18) {
                pv_prediction.push_back(700);
            }
            else {
                pv_prediction.push_back(0);
            }

            if (h > 18) {
                load_prediction.push_back(600);
            }
            else {
                load_prediction.push_back(500);
            }

            if (h > 6 && h < 12) {
                expectedPower.push_back(-50);
            }
            else if (h == 12) {
                if (step == 0) {
                    expectedPower.push_back(-50);
                }
                else if (step == 1) {
                    expectedPower.push_back(-22.3);
                }
                else {
                    expectedPower.push_back(0);
                }
            }
            else if (h > 18) {
                expectedPower.push_back(50);
            }
            else {
                expectedPower.push_back(0);
            }
            
        }
    }

    dispatchAutoBTM->update_load_data(load_prediction);
    dispatchAutoBTM->update_pv_data(pv_prediction);

    batteryPower = dispatchAutoBTM->getBatteryPower();
    batteryPower->connectionMode = ChargeController::AC_CONNECTED;

    // Battery will charge when PV is available, then discharge when load increases at 7 pm
    int index = 0;
    for (size_t h = 0; h < 24; h++) {
        for (size_t step = 0; step < 4; step++) {
            batteryPower->powerLoad = 500;
            batteryPower->powerPV = 0;
            if (h > 6 && h < 18) {
                batteryPower->powerPV = 700; // Match the predicted PV
            }
            else if (h > 18) {
                batteryPower->powerLoad = 600; // Match the predicted load
            }
            dispatchAutoBTM->dispatch(0, h, step);
            EXPECT_NEAR(batteryPower->powerBatteryDC, expectedPower[index], 0.2) << " error in expected at step " << index;
            index++;
        }
    }
}