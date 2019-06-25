#ifndef _TCSMOLTEN_SALT_CASES_H_
#define _TCSMOLTEN_SALT_CASES_H_

#include <map>
#include "../input_cases/code_generator_utilities.h"
#include "tcsmolten_salt_common_data.h"

/**
*   Data for high-level integration tests that verifies whether results for a molten salt power tower
*   plant in Daggett, CA matches expected results.
*   Data generated from code-generator (Shift+F5) within SAM UI.
*   Test uses SSCAPI interfaces (similiar to SDK usage) to pass and receive data to tcsmolten_salt
*/

// Power Tower molten salt default congifuration
// Rankine Power Cycle: Fixed pressure & Air-cooled
int tcsmolten_salt_daggett_default(ssc_data_t &data)
{
    tcsmolten_salt_default(data);
	int status = run_module(data, "tcsmolten_salt");

    //single_owner_default(data);
    //status += run_module(data, "singleowner");

	return status;
}

// Power Tower molten salt with alternative Rankine Cycle configuration
// Rankine Power Cycle: Sliding pressure & Air-cooled
// Rest default configurations
int tcsmolten_salt_daggett_sliding_pressure(ssc_data_t &data)
{
	tcsmolten_salt_default(data);

	ssc_data_set_number(data, "tech_type", 3);
	
	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power tower molten salt with alternative Rankine Cycle configuration
// Condenser type alternative: Evaporative 
// Rest default configurations 
int tcsmolten_salt_daggett_evap_condenser(ssc_data_t &data)
{
	tcsmolten_salt_default(data);
	ssc_data_set_number(data, "CT", 1);
	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power tower molten salt with alternative Rankine Cycle configuration
// Condenser type alternative: Hybrid
// Rest default configurations 
int tcsmolten_salt_daggett_hybrid_condenser(ssc_data_t &data)
{
	tcsmolten_salt_default(data);
	ssc_data_set_number(data, "CT", 3);
	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power tower molten salt with alternative Rankine Cycle configuration
// Condenser type alternative: Radiative
// Rest default configurations 
int tcsmolten_salt_daggett_radiative_condenser(ssc_data_t &data)
{
	tcsmolten_salt_default(data);
	// Start of radiative-cooling metrics
	ssc_data_set_number(data, "h_ctes_tank_min", 1);
	ssc_data_set_number(data, "ctes_tshours", 15);
	ssc_data_set_number(data, "ctes_field_fl", 4);
	ssc_data_set_number(data, "h_ctes_tank", 30);
	ssc_data_set_number(data, "u_ctes_tank", 0.40000000000000002);
	ssc_data_set_number(data, "ctes_tankpairs", 1);
	ssc_data_set_number(data, "T_ctes_cold_design", 5);
	ssc_data_set_number(data, "T_ctes_warm_design", 10);
	ssc_data_set_number(data, "T_ctes_warm_ini", 20);
	ssc_data_set_number(data, "T_ctes_cold_ini", 10);
	ssc_data_set_number(data, "f_ctes_warm_ini", 0);
	ssc_data_set_number(data, "rad_multiplier", 1.5);
	ssc_data_set_number(data, "m_dot_radpanel", 8);
	ssc_data_set_number(data, "n_rad_tubes", 100);
	ssc_data_set_number(data, "W_rad_tubes", 0.050000000000000003);
	ssc_data_set_number(data, "L_rad", 100);
	ssc_data_set_number(data, "th_rad_panel", 0.002);
	ssc_data_set_number(data, "D_rad_tubes", 0.02);
	ssc_data_set_number(data, "k_panel", 235);
	ssc_data_set_number(data, "epsilon_radtop", 0.94999999999999996);
	ssc_data_set_number(data, "epsilon_radbot", 0.070000000000000007);
	ssc_data_set_number(data, "epsilon_radgrnd", 0.90000000000000002);
	ssc_data_set_number(data, "L_rad_sections", 10);
	ssc_data_set_number(data, "epsilon_radHX", 0.80000000000000004);
	ssc_data_set_number(data, "ctes_type", 0);
	ssc_data_set_number(data, "helio_area_tot", 1269054.5);
	ssc_data_set_number(data, "radiator_unitcost", 13);
	ssc_data_set_number(data, "radiator_installcost", 22);
	ssc_data_set_number(data, "radiator_fluidcost", 0.34000000357627869);
	ssc_data_set_number(data, "radfluid_vol_ratio", 3);
	ssc_data_set_number(data, "ctes_cost", 0.69999998807907104);
	ssc_data_set_number(data, "rad_pressuredrop", 75);
	//End of radiative-cooling metrics
	ssc_data_set_number(data, "CT", 4);
	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power Tower molten salt with alternative Rankine Cycle configuration
// Tower and Receiver alternative: Flow Pattern 
// Rest default configurations
int tcsmolten_salt_daggett_flow_pattern(ssc_data_t &data)
{
	tcsmolten_salt_default(data);

	ssc_data_set_number(data, "Flow_type", 8);

	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power Tower molten salt with alternative Rankine Cycle configuration
// Location alternative: Tucson, Arizona 
// Rest default configurations
int tcsmolten_salt_daggett_Tucson_AZ(ssc_data_t &data)
{
	tcsmolten_salt_default(data);

	ssc_data_set_string(data, "solar_resource_file", "C:/Users/kfung/Documents/SAM/sam_dev/SAM/deploy/solar_resource/tucson_az_32.116521_-110.933042_psmv3_60_tmy.csv");

	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power Tower molten salt with power cycle alternative: User Defined
// Rest default configurations
int tcsmolten_salt_daggett_UD_default(ssc_data_t &data)
{
	tcsmolten_salt_default(data);

	ssc_data_set_number(data, "pc_config", 1);
	set_matrix(data, "ud_ind_od", "C:/RPP Summer/C++/SAM Hierarchy/SAM CSP Models/3 - CSP power tower molten salt/PPA single owner (utility)/UserDefined_unit_test_default/ud_ind_od.csv", 180, 7);

	ssc_data_set_number(data, "ud_m_dot_htf_low", 0.29999999999999999);
	ssc_data_set_number(data, "ud_m_dot_htf_high", 1.2);

	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power Tower molten salt with power cycle alternative: Super Critical CO2
// Rest default configurations
int tcsmolten_salt_daggett_SCO2_default(ssc_data_t &data)
{
	tcsmolten_salt_default(data);

	ssc_data_set_number(data, "pc_config", 2);
	ssc_data_set_number(data, "cycle_cutoff_frac", 0.5);
		
	// Start of super critical CO2 metrics
	ssc_data_set_number(data, "sco2ud_T_htf_cold_calc", 406.039794921875);
	ssc_data_set_number(data, "sco2ud_T_htf_low", 554);
	ssc_data_set_number(data, "sco2ud_T_htf_high", 589);

	ssc_data_set_number(data, "sco2ud_T_amb_high", 45);
	ssc_data_set_number(data, "sco2ud_m_dot_htf_low", 0.5);
	ssc_data_set_number(data, "sco2ud_m_dot_htf_high", 1.0499999523162842);
	ssc_number_t p_sco2ud_T_htf_ind_od[65] = { 554, 0.50001432179685623, 0.96932004909372826, 0.97558944094670463, 0.56452945008574118, 0.99212119137385479, 0.9938261663184943, 0.071046760698792344, 1.0516901234966409, 1.0396677815546937, 1, 1, 1, 562.75, 0.50000677254611736, 0.98273822965810698, 0.98931005948737616, 0.55442312464765453, 0.99593839560635933, 0.99813862855158975, 0.060760248142716182, 1.0280675561194188, 1.0216094704370726, 1, 1, 1, 571.5, 0.49997035485832741, 0.99560036541912367, 1.0030665958141747, 0.54540906175814596, 0.99964495720997093, 1.0023929148428683, 0.052633463645261176, 1.0056543163255209, 1.0033307681195913, 1, 1, 1, 580.25, 0.50001678576431519, 0.99981330235493204, 1.0149012834308118, 0.53755371644427918, 0.99437061481748712, 1.0057187757624548, 0.046124783184180999, 0.93267305740289486, 0.97564080126247599, 1, 1, 1, 589, 0.49998766910986947, 0.99997642865903091, 1.0280965929880774, 0.53035396718324523, 0.98587808938966315, 1.0103635810622889, 0.040778740942652915, 0.84986379353651254, 0.96107738725047209, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_T_htf_ind_od", p_sco2ud_T_htf_ind_od, 5, 13);
	ssc_number_t p_sco2ud_T_amb_ind_od[130] = { 0, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.059164848919520591, 0.049933864673572616, 0.04548467867978704, 1, 1, 1, 5, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.097133136927079936, 0.082248959886362452, 0.075269394493921518, 1, 1, 1, 10, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.17314165365655804, 0.14726896648379706, 0.13576325670205261, 1, 1, 1, 15, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.3481506775773433, 0.29853487098289033, 0.27855988861884273, 1, 1, 1, 20, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.85719459330059711, 0.74767538224853725, 0.71410844002614948, 1, 1, 1, 25, 0.99998860165458137, 0.99998405506376475, 0.99994129487763628, 0.97834420606252215, 0.9592086954026382, 0.94639328546002388, 1.4397512132898596, 1.1099623611534934, 0.9289610766286478, 1, 1, 1, 30, 0.99997868773200105, 1.0000128744625323, 0.99987390166815182, 0.99986135777103136, 0.97846151925556812, 0.96428182700735732, 1.2885473732704416, 1.0097961360792755, 0.85212892165494525, 1, 1, 1, 35, 0.96932004909372826, 0.99995022500741981, 0.99997642865903091, 0.99212119137385479, 0.99999459906789145, 0.98587808938966315, 1.0516901234966409, 1.0033307681195913, 0.84986379353651254, 1, 1, 1, 40, 0.85681928090544024, 0.88648580427756085, 0.90755440545490784, 0.8967547597723905, 0.90655814175453875, 0.91360819421216066, 0.54638640488302492, 0.52332590711799631, 0.50841120332212841, 1, 1, 1, 45, 0.76192612755033284, 0.78992076166486025, 0.81009772614290565, 0.81887517513574226, 0.82799762047592962, 0.83504194672755783, 0.32667431104075889, 0.31463845368914112, 0.30664767313185981, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_T_amb_ind_od", p_sco2ud_T_amb_ind_od, 10, 13);
	ssc_number_t p_sco2ud_m_dot_htf_ind_od[130] = { 0.5, 0.50000238394483887, 0.50002030400496988, 0.5000072744279479, 0.49996830468452913, 0.54311461140321193, 0.58949291750771449, 0.0023965079935530688, 0.050651289208334289, 0.085268991630535099, 1, 1, 1, 0.56111111111111112, 0.56107350053341665, 0.56109752841228611, 0.56110469253490813, 0.55257347648896971, 0.59674948077268875, 0.64372698634700765, 0.0035623149303332731, 0.076089576895326735, 0.12158112224599875, 1, 1, 1, 0.62222222222222223, 0.62224697121064898, 0.62224996267725707, 0.62219761804463092, 0.60616131300962228, 0.65145619071565242, 0.69969734374588888, 0.0052256619247860641, 0.11370919032872756, 0.17234788816884622, 1, 1, 1, 0.68333333333333335, 0.68334763160686485, 0.68332772806833242, 0.68334268666386189, 0.66063755666452395, 0.70667012650879169, 0.75616720875118448, 0.0076071355040999147, 0.16722335929420953, 0.24228904960439612, 1, 1, 1, 0.74444444444444446, 0.74441099641078146, 0.74443754704645426, 0.73579757426674453, 0.7154614610083625, 0.76238207877819242, 0.80635338615523044, 0.010993657103543011, 0.24183918938496599, 0.28923568019902324, 1, 1, 1, 0.80555555555555558, 0.80548586203577432, 0.80556625128549619, 0.7607325689541361, 0.7709115279333274, 0.81874600280477805, 0.81846324371170665, 0.015863026451133713, 0.34650772248743805, 0.32712367869313513, 1, 1, 1, 0.8666666666666667, 0.86665068706416915, 0.86667726624963815, 0.77310372269008887, 0.82666048629288214, 0.87575544351530044, 0.82250334117333646, 0.022915833888653158, 0.49058181757621305, 0.32138671984149092, 1, 1, 1, 0.92777777777777781, 0.92781567340041837, 0.92781937609673271, 0.78228939831004085, 0.88241774237123771, 0.93313651551826904, 0.82559824503018264, 0.033028022568911568, 0.6869968410833619, 0.31804744512991351, 1, 1, 1, 0.98888888888888893, 0.98860321834099996, 0.98888850977399578, 0.78897052574490523, 0.93832104872570143, 0.99049121752897784, 0.82770087400040337, 0.049618846148749549, 0.94725737476210103, 0.31520682775233339, 1, 1, 1, 1.05, 1.0487348778724641, 1.0062218585376423, 0.79376542360284852, 1.0039295318936428, 1.0043865029637598, 0.82928412460314016, 0.049807927876335194, 0.99339517007581468, 0.31300940662606114, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_m_dot_htf_ind_od", p_sco2ud_m_dot_htf_ind_od, 10, 13);
	ssc_data_set_number(data, "_sco2_P_high_limit", 25);
	ssc_data_set_number(data, "_sco2_P_ref", 115);
	ssc_data_set_number(data, "_sco2_T_amb_des", 35);
	ssc_data_set_number(data, "_sco2_T_approach", 10);
	ssc_data_set_number(data, "_sco2_T_htf_hot_des", 574);
	ssc_data_set_number(data, "_sco2_deltaT_PHX", 20);
	ssc_data_set_number(data, "_sco2_design_eff", 0.41200000047683716);
	ssc_data_set_number(data, "_sco2_eta_c", 0.88999998569488525);
	ssc_data_set_number(data, "_sco2_eta_t", 0.89999997615814209);
	ssc_data_set_number(data, "_sco2_recup_eff_max", 0.95999997854232788);
	//End of super critical CO2 metrics

	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power Tower molten salt with power cycle alternative: Super Critical CO2
// Cycle Configuration alternative: Partial Cooling
// Rest default configurations
int tcsmolten_salt_daggett_SCO2_partial_cooling(ssc_data_t &data)
{
	tcsmolten_salt_default(data);
	
	ssc_data_set_number(data, "pc_config", 2);
	ssc_data_set_number(data, "cycle_cutoff_frac", 0.5);
	// Start of super critical CO2 metrics
	ssc_data_set_number(data, "sco2_cycle_config", 2);

	ssc_data_set_number(data, "sco2ud_T_htf_cold_calc", 354.8427734375);
	ssc_data_set_number(data, "sco2ud_T_htf_low", 554);
	ssc_data_set_number(data, "sco2ud_T_htf_high", 589);

	ssc_data_set_number(data, "sco2ud_T_amb_high", 45);
	ssc_data_set_number(data, "sco2ud_m_dot_htf_low", 0.5);
	ssc_data_set_number(data, "sco2ud_m_dot_htf_high", 1.0499999523162842);
	ssc_number_t p_sco2ud_T_htf_ind_od[65] = { 554, 0.49999352886459142, 0.96525561209463806, 0.97453395561145839, 0.62911366508823352, 0.98998074672002789, 0.99261217903413035, 0.20247797682275048, 1.0571168076843547, 1.0432895732028127, 1, 1, 1, 562.75, 0.49999364663999546, 0.98061760093183636, 0.98945608039614341, 0.59967747034505758, 0.99410410545590111, 0.99692477104310284, 0.17800016270512209, 1.0348516156853151, 1.0211725729287384, 1, 1, 1, 571.5, 0.49999395161728027, 0.99563145139446119, 1.0038535082905322, 0.58306031118146817, 0.99832427864796236, 1.001449148486844, 0.16124320857207705, 1.0092594720500885, 1.0025470111145369, 1, 1, 1, 580.25, 0.49999438710690025, 1.0000368631016281, 1.0187996347167014, 0.57310398959762909, 0.99215602847837348, 1.0059800813551822, 0.14338401700982784, 0.9341583009417217, 0.98266060214587514, 1, 1, 1, 589, 0.50001605482790912, 0.99999012779922869, 1.0325220180423378, 0.56534529941933243, 0.9816011558820481, 1.0098950333460388, 0.12932201013498895, 0.84387453074601659, 0.96199109269179472, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_T_htf_ind_od", p_sco2ud_T_htf_ind_od, 5, 13);
	ssc_number_t p_sco2ud_T_amb_ind_od[130] = { 0, 0.99997428799188914, 0.99999000874401356, 0.99999963664033542, 1.0096260890795448, 0.97647524655927898, 0.95539332954343525, 0.035964053686654389, 0.030460203665356428, 0.028191373083630726, 1, 1, 1, 5, 0.99997428799188914, 0.99999000874401356, 0.99999963664033542, 1.0096260890795448, 0.97647524655927898, 0.95539332954343525, 0.054169401117576316, 0.046164874738715223, 0.043090992060877832, 1, 1, 1, 10, 0.99997428799188914, 0.99999000874401356, 0.99999963664033542, 1.0096260890795448, 0.97647524655927898, 0.95539332954343525, 0.086054162974292386, 0.074011959990269383, 0.069988333857598825, 1, 1, 1, 15, 0.99997428799188914, 0.99999000874401356, 0.99999963664033542, 1.0096260890795448, 0.97647524655927898, 0.95539332954343525, 0.14717747411619553, 0.12834741606804084, 0.12359755317608473, 1, 1, 1, 20, 0.99997428799188914, 0.99999000874401356, 0.99999963664033542, 1.0096260890795448, 0.97647524655927898, 0.95539332954343525, 0.27882175950298732, 0.24810999613169693, 0.24587350287625651, 1, 1, 1, 25, 0.99998001476123333, 0.99998252902816598, 0.99991197104226259, 1.0098815301216097, 0.97647895095481074, 0.9554677877793778, 0.59120853683278496, 0.54403699709247888, 0.56813028411712974, 1, 1, 1, 30, 0.99998001476123333, 0.99998700539505325, 1.000003594937197, 1.0098815301216097, 0.97801555014110308, 0.95937811970467868, 1.6874663271788872, 1.1677785621376786, 0.92812586911858419, 1, 1, 1, 35, 0.96525561209463806, 0.99994365838368371, 0.99999012779922869, 0.98998074672002789, 1.0001162551906568, 0.9816011558820481, 1.0571168076843547, 1.0070553661423967, 0.84387453074601659, 1, 1, 1, 40, 0.88091956289263618, 0.91354408714037638, 0.93692898396657309, 0.92804590812890486, 0.93898338187710573, 0.94720156997882032, 0.77791598161892206, 0.7475571669584532, 0.72852820207159907, 1, 1, 1, 45, 0.80443081580069309, 0.83588054350931573, 0.85830802419616214, 0.87954062349121198, 0.89162501172294772, 0.90100255955577613, 0.71796263227634882, 0.69604875226586571, 0.68078331511457812, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_T_amb_ind_od", p_sco2ud_T_amb_ind_od, 10, 13);
	ssc_number_t p_sco2ud_m_dot_htf_ind_od[130] = { 0.5, 0.50001158587629013, 0.49999335234425468, 0.500009458086906, 0.52092523582781203, 0.580310601704488, 0.67277741730869234, 0.0066297710364970602, 0.15612995926951076, 0.42538208998154886, 1, 1, 1, 0.56111111111111112, 0.56112632572922161, 0.56109347634533013, 0.56112858298132773, 0.5676475361894191, 0.62646030027815847, 0.70338416085113653, 0.0079531402579119982, 0.18764587089730347, 0.43103981940440877, 1, 1, 1, 0.62222222222222223, 0.62221611814605471, 0.62221274231112988, 0.62222151074161314, 0.61455395777278332, 0.67446637440230506, 0.74670855688273574, 0.0093884633943930561, 0.22842611147672137, 0.48833317891759392, 1, 1, 1, 0.68333333333333335, 0.68329224890757501, 0.68333522189257412, 0.68331145370876678, 0.66231318458618582, 0.72371156880387011, 0.7949045334243946, 0.011139413945746518, 0.28028443088130395, 0.57482477745595617, 1, 1, 1, 0.74444444444444446, 0.74445060439362043, 0.74444232493970608, 0.74442697568885108, 0.71280359548337557, 0.77393932493368434, 0.84599994004797685, 0.01370986733027353, 0.34683195143613776, 0.69088300755849497, 1, 1, 1, 0.80555555555555558, 0.80554205452706595, 0.80553118613158747, 0.78568541702380978, 0.76617945177385471, 0.82545035439296532, 0.87282832981226932, 0.018334310087357693, 0.43577215265376867, 0.73125604358596707, 1, 1, 1, 0.8666666666666667, 0.86667780683097451, 0.86669111505864649, 0.80779790168115828, 0.82501645350095432, 0.8784837343548566, 0.88083521806059473, 0.031013715053052799, 0.55720344212317163, 0.71564348223866958, 1, 1, 1, 0.92777777777777781, 0.92778930075110044, 0.92781165563938151, 0.82346900197673678, 0.89420782417679856, 0.9332817335240674, 0.88681855363756823, 0.030225663571636099, 0.72555609695067691, 0.70381015654357315, 1, 1, 1, 0.98888888888888893, 0.98891033574992371, 0.98886027855958214, 0.8342986400696234, 0.96400610586573099, 0.98968856703989938, 0.89098743214344123, 0.030057676976388854, 0.95810218483069376, 0.69690700803894567, 1, 1, 1, 1.05, 1.0499204736064125, 1.0082881287098067, 0.84167433259869806, 1.0322051570968707, 1.002564506765949, 0.89389762859965882, 0.034640376520654041, 0.99538596406341329, 0.69252556580813951, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_m_dot_htf_ind_od", p_sco2ud_m_dot_htf_ind_od, 10, 13);
	ssc_data_set_number(data, "_sco2_P_high_limit", 25);
	ssc_data_set_number(data, "_sco2_P_ref", 115);
	ssc_data_set_number(data, "_sco2_T_amb_des", 35);
	ssc_data_set_number(data, "_sco2_T_approach", 10);
	ssc_data_set_number(data, "_sco2_T_htf_hot_des", 574);
	ssc_data_set_number(data, "_sco2_deltaT_PHX", 20);
	ssc_data_set_number(data, "_sco2_design_eff", 0.41200000047683716);
	ssc_data_set_number(data, "_sco2_eta_c", 0.88999998569488525);
	ssc_data_set_number(data, "_sco2_eta_t", 0.89999997615814209);
	ssc_data_set_number(data, "_sco2_recup_eff_max", 0.95999997854232788);
	//End of super critical CO2 metrics
	
	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}

// Power Tower molten salt with power cycle alternative: Super Critical CO2
// Materials and Flow alternative: Flow pattern 2 instead of 1
// Rest default configurations
int tcsmolten_salt_daggett_SCO2_flow_pattern_2(ssc_data_t &data)
{
	tcsmolten_salt_default(data);

	ssc_data_set_number(data, "Flow_type", 2);
	ssc_data_set_number(data, "pc_config", 2);
	ssc_data_set_number(data, "cycle_cutoff_frac", 0.5);

	// Start of super critical CO2 metrics
	ssc_data_set_number(data, "sco2ud_T_htf_cold_calc", 406.039794921875);
	ssc_data_set_number(data, "sco2ud_T_htf_low", 554);
	ssc_data_set_number(data, "sco2ud_T_htf_high", 589);
	ssc_data_set_number(data, "sco2ud_T_amb_high", 45);
	ssc_data_set_number(data, "sco2ud_m_dot_htf_low", 0.5);
	ssc_data_set_number(data, "sco2ud_m_dot_htf_high", 1.0499999523162842);
	ssc_number_t p_sco2ud_T_htf_ind_od[65] = { 554, 0.50001432179685623, 0.96932004909372826, 0.97558944094670463, 0.56452945008574118, 0.99212119137385479, 0.9938261663184943, 0.071046760698792344, 1.0516901234966409, 1.0396677815546937, 1, 1, 1, 562.75, 0.50000677254611736, 0.98273822965810698, 0.98931005948737616, 0.55442312464765453, 0.99593839560635933, 0.99813862855158975, 0.060760248142716182, 1.0280675561194188, 1.0216094704370726, 1, 1, 1, 571.5, 0.49997035485832741, 0.99560036541912367, 1.0030665958141747, 0.54540906175814596, 0.99964495720997093, 1.0023929148428683, 0.052633463645261176, 1.0056543163255209, 1.0033307681195913, 1, 1, 1, 580.25, 0.50001678576431519, 0.99981330235493204, 1.0149012834308118, 0.53755371644427918, 0.99437061481748712, 1.0057187757624548, 0.046124783184180999, 0.93267305740289486, 0.97564080126247599, 1, 1, 1, 589, 0.49998766910986947, 0.99997642865903091, 1.0280965929880774, 0.53035396718324523, 0.98587808938966315, 1.0103635810622889, 0.040778740942652915, 0.84986379353651254, 0.96107738725047209, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_T_htf_ind_od", p_sco2ud_T_htf_ind_od, 5, 13);
	ssc_number_t p_sco2ud_T_amb_ind_od[130] = { 0, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.059164848919520591, 0.049933864673572616, 0.04548467867978704, 1, 1, 1, 5, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.097133136927079936, 0.082248959886362452, 0.075269394493921518, 1, 1, 1, 10, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.17314165365655804, 0.14726896648379706, 0.13576325670205261, 1, 1, 1, 15, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.3481506775773433, 0.29853487098289033, 0.27855988861884273, 1, 1, 1, 20, 0.99994012767121321, 0.99974326147411507, 0.99987485850649338, 0.970379288808072, 0.95027470619969945, 0.93683012616718919, 0.85719459330059711, 0.74767538224853725, 0.71410844002614948, 1, 1, 1, 25, 0.99998860165458137, 0.99998405506376475, 0.99994129487763628, 0.97834420606252215, 0.9592086954026382, 0.94639328546002388, 1.4397512132898596, 1.1099623611534934, 0.9289610766286478, 1, 1, 1, 30, 0.99997868773200105, 1.0000128744625323, 0.99987390166815182, 0.99986135777103136, 0.97846151925556812, 0.96428182700735732, 1.2885473732704416, 1.0097961360792755, 0.85212892165494525, 1, 1, 1, 35, 0.96932004909372826, 0.99995022500741981, 0.99997642865903091, 0.99212119137385479, 0.99999459906789145, 0.98587808938966315, 1.0516901234966409, 1.0033307681195913, 0.84986379353651254, 1, 1, 1, 40, 0.85681928090544024, 0.88648580427756085, 0.90755440545490784, 0.8967547597723905, 0.90655814175453875, 0.91360819421216066, 0.54638640488302492, 0.52332590711799631, 0.50841120332212841, 1, 1, 1, 45, 0.76192612755033284, 0.78992076166486025, 0.81009772614290565, 0.81887517513574226, 0.82799762047592962, 0.83504194672755783, 0.32667431104075889, 0.31463845368914112, 0.30664767313185981, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_T_amb_ind_od", p_sco2ud_T_amb_ind_od, 10, 13);
	ssc_number_t p_sco2ud_m_dot_htf_ind_od[130] = { 0.5, 0.50000238394483887, 0.50002030400496988, 0.5000072744279479, 0.49996830468452913, 0.54311461140321193, 0.58949291750771449, 0.0023965079935530688, 0.050651289208334289, 0.085268991630535099, 1, 1, 1, 0.56111111111111112, 0.56107350053341665, 0.56109752841228611, 0.56110469253490813, 0.55257347648896971, 0.59674948077268875, 0.64372698634700765, 0.0035623149303332731, 0.076089576895326735, 0.12158112224599875, 1, 1, 1, 0.62222222222222223, 0.62224697121064898, 0.62224996267725707, 0.62219761804463092, 0.60616131300962228, 0.65145619071565242, 0.69969734374588888, 0.0052256619247860641, 0.11370919032872756, 0.17234788816884622, 1, 1, 1, 0.68333333333333335, 0.68334763160686485, 0.68332772806833242, 0.68334268666386189, 0.66063755666452395, 0.70667012650879169, 0.75616720875118448, 0.0076071355040999147, 0.16722335929420953, 0.24228904960439612, 1, 1, 1, 0.74444444444444446, 0.74441099641078146, 0.74443754704645426, 0.73579757426674453, 0.7154614610083625, 0.76238207877819242, 0.80635338615523044, 0.010993657103543011, 0.24183918938496599, 0.28923568019902324, 1, 1, 1, 0.80555555555555558, 0.80548586203577432, 0.80556625128549619, 0.7607325689541361, 0.7709115279333274, 0.81874600280477805, 0.81846324371170665, 0.015863026451133713, 0.34650772248743805, 0.32712367869313513, 1, 1, 1, 0.8666666666666667, 0.86665068706416915, 0.86667726624963815, 0.77310372269008887, 0.82666048629288214, 0.87575544351530044, 0.82250334117333646, 0.022915833888653158, 0.49058181757621305, 0.32138671984149092, 1, 1, 1, 0.92777777777777781, 0.92781567340041837, 0.92781937609673271, 0.78228939831004085, 0.88241774237123771, 0.93313651551826904, 0.82559824503018264, 0.033028022568911568, 0.6869968410833619, 0.31804744512991351, 1, 1, 1, 0.98888888888888893, 0.98860321834099996, 0.98888850977399578, 0.78897052574490523, 0.93832104872570143, 0.99049121752897784, 0.82770087400040337, 0.049618846148749549, 0.94725737476210103, 0.31520682775233339, 1, 1, 1, 1.05, 1.0487348778724641, 1.0062218585376423, 0.79376542360284852, 1.0039295318936428, 1.0043865029637598, 0.82928412460314016, 0.049807927876335194, 0.99339517007581468, 0.31300940662606114, 1, 1, 1 };
	ssc_data_set_matrix(data, "sco2ud_m_dot_htf_ind_od", p_sco2ud_m_dot_htf_ind_od, 10, 13);
	ssc_data_set_number(data, "_sco2_P_high_limit", 25);
	ssc_data_set_number(data, "_sco2_P_ref", 115);
	ssc_data_set_number(data, "_sco2_T_amb_des", 35);
	ssc_data_set_number(data, "_sco2_T_approach", 10);
	ssc_data_set_number(data, "_sco2_T_htf_hot_des", 574);
	ssc_data_set_number(data, "_sco2_deltaT_PHX", 20);
	ssc_data_set_number(data, "_sco2_design_eff", 0.41200000047683716);
	ssc_data_set_number(data, "_sco2_eta_c", 0.88999998569488525);
	ssc_data_set_number(data, "_sco2_eta_t", 0.89999997615814209);
	ssc_data_set_number(data, "_sco2_recup_eff_max", 0.95999997854232788);
	//End of super critical CO2 metrics
	
	int status = run_module(data, "tcsmolten_salt");

	//single_owner_default(data);
	//status += run_module(data, "singleowner");

	return status;
}


#endif
