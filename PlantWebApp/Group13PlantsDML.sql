-- 	Plant Database
-- 	Group 13
-- 	Russell Eck and Morgan Eck
--	Data Manipulation Queries

--
--	INSERT STATEMENTS				 
--					

-- Query for add a new climate functionality. 
-- Colon : character being used to denote the variables that will have data from the backend programming language.
INSERT INTO `climate` (`lowest_temperature`, `highest_temperature`, `humidity`) VALUES
(:lowest_temperature, :highest_temperature, :humidty_range_0_to_100);

-- Query for add a new sunlight functionality. 
-- Colon : character being used to denote the variables that will have data from the backend programming language.
INSERT INTO `sunlight` (`sunlight_hours`, `full_sunlight`, `medium_sunlight`, `low_sunlight`) VALUES
(:sunlight_hours_dropdown_range_1_to_24, :full_sunlight_dropdown_true_false, :medium_sunlight_dropdown_true_false, :low_sunlight_dropdown_true_false);

-- Query for add a new soil functionality. 
-- Colon : character being used to denote the variables that will have data from the backend programming language.
INSERT INTO `soil` (`soil_type`, `soil_ph`, `fertilizer`) VALUES
(:soil_type, :soil_ph_dropdown_0_to_14, :fertilizer_drowdown_true_false);

-- Query for add a new watering_cycle functionality. 
-- Colon : character being used to denote the variables that will have data from the backend programming language.
INSERT INTO `watering_cycle` (`days`) VALUES
(:days);

-- Query for add a new plants functionality. 
-- Colon : character being used to denote the variables that will have data from the backend programming language.
INSERT INTO `plants` (`genus`, `species`, `common_name`, `required_light`, `climate_type`) VALUES 
(:genus, :species, :common_name, :required_light_id_from_sunlight, :climate_type_id_from_climate);

-- Query for add a new plants_watering link functionality. 
-- Colon : character being used to denote the variables that will have data from the backend programming language.
INSERT INTO `plants_watering` (`plant_id`, `watering_id`) VALUES
(:plant_id_from_plants, :watering_id_from_watering_cycle);

-- Query for add a new plant_soil link functionality. 
-- Colon : character being used to denote the variables that will have data from the backend programming language.
INSERT INTO `plants_soil` (`plant_id`, `soil_id`) VALUES
(:plant_id_from_plants, :soil_id_from_soil);



--
--	UPDATE STATEMENTS				 
--	

-- Update a climate data based on submission of the Update Climate form 
UPDATE `climate` SET `lowest_temperature` = :lowest_temperature_input, `highest_temperature` = :highest_temperature_input, 
`humidity` = :humidty_range_0_to_100 
WHERE `id` = :climate_ID_from_the_update_form;

-- Update a sunlight data based on submission of the Update Sunlight form 
UPDATE `sunlight` SET `sunlight_hours` = :sunlight_hours_dropdown_range_1_to_24, `full_sunlight` = :full_sunlight_dropdown_true_false, 
`medium_sunlight` = :medium_sunlight_dropdown_true_false, `low_sunlight` = :low_sunlight_dropdown_true_false 
WHERE `id` = :sunlight_ID_from_the_update_form;

-- Update a soil data based on submission of the Update Soil form 
UPDATE `soil` SET `soil_type` = :soil_type_input, `soil_ph` = :soil_ph_dropdown_0_to_14, `fertilizer` = fertilizer_drowdown_true_false
WHERE `id` = :soil_ID_from_the_update_form;

-- Update a watering_cycle data based on submission of the Update Watering_Cycle form 
UPDATE `watering_cycle` SET `days` = :days_input WHERE `id` = :watering_cycle_from_the_update_form;

-- Update a plants data based on submission of the Update Plant form 
UPDATE `plants` SET `genus` = :genus_input, `species` = :species_input, `common_name` = :common_name_input, 
`required_light` = :required_light_id_from_sunlight_input, `climate_type` = :climate_type_id_from_climate_input
WHERE `id` = :plants_ID_from_the_update_form;

-- Update a plants_watering data based on submission of the Update Plant_watering form 
UPDATE `plants_watering` SET `plant_id` = :plant_id_input, `watering_id` = :watering_id_input 
WHERE `plant_id` = :plant_id_from_the_update_form AND `watering_id` = :watering_id_from_the_update_form;

-- Update a plant_soil data based on submission of the Update Plant_soil form 
UPDATE `plants_soil` SET `plant_id` = :plant_id_input, `soil_id` = :soil_id_input 
WHERE `plant_id` = :plant_id_from_the_update_form AND `soil_id` = :soil_id_from_the_updatet_form;



--
--	DELETE STATEMENTS				 
--	

DELETE FROM `climate` WHERE `id` = :row_delete_button_from_climate_page;

DELETE FROM `sunlight` WHERE `id` = :row_delete_button_from_sunlight_page;

DELETE FROM `soil` WHERE `id` = :row_delete_button_from_soil_page;

DELETE FROM `watering_cycle` WHERE `id` = :row_delete_button_from_watering_cycle_page;

DELETE FROM `plants` WHERE `id` = :row_delete_button_from_plants_page;

-- dis-associate a watering_cycle from a plant (M-to-M relationship deletion)
DELETE FROM `plants_watering` WHERE `plant_id` = :id_from_list_of_plant_ids 
AND `watering_id` = :id_from_list_of_watering_ids;

-- dis-associate a soil from a plant (M-to-M relationship deletion)
DELETE FROM `plants_soil` WHERE `plant_id` = :id_from_list_of_plant_ids 
AND `soil_id` = :id_from_list_of_soil_ids;




--
--	QUERY STATEMENTS				 
--	

-- Display plants table
SELECT * FROM `plants`;

-- Display climate table
SELECT * FROM `climate`;

-- Display sunlight table
SELECT * FROM `sunlight`;

-- Display watering_cycle table
SELECT * FROM `watering_cycle`;

-- Display soil table
SELECT * FROM `soil`;

-- Display plants_watering table
SELECT * FROM `plants_watering`;

-- Display plants_soil table
SELECT * FROM `plants_soil`;

-- Displays plants that tolerate high temperatures --
SELECT plants.genus, plants.species, plants.common_name
FROM climate, plants
WHERE climate.id = plants.climate_type
AND highest_temperature > 90;

-- Displays plants that tolerate low temperatures --
SELECT plants.genus, plants.species, plants.common_name
FROM climate, plants
WHERE climate.id = plants.climate_type
AND lowest_temperature < 20;

-- Displays plants that are good for low light and not full sunlight
SELECT plants.genus, plants.species, plants.common_name
FROM sunlight, plants
WHERE sunlight.id = plants.required_light
AND low_sunlight = 1
AND full_sunlight = 0;

-- Displays plants that are good for full light and not low sunlight
SELECT plants.genus, plants.species, plants.common_name
FROM sunlight, plants
WHERE sunlight.id = plants.required_light
AND low_sunlight = 0
AND full_sunlight = 1;

-- Displays plants that need to be watered every day --
SELECT plants.genus, plants.species, plants.common_name
FROM watering_cycle, plants_watering, plants
WHERE watering_cycle.id = plants_watering.watering_id
AND plants_watering.plant_id = plants.id
AND days = 0;

-- Displays plants that need to be watered weekly or more frequently --
SELECT plants.genus, plants.species, plants.common_name
FROM watering_cycle, plants_watering, plants
WHERE watering_cycle.id = plants_watering.watering_id
AND plants_watering.plant_id = plants.id
AND days <= 7;

-- Displays plants that need to be watered weekly or less frequently --
SELECT plants.genus, plants.species, plants.common_name
FROM watering_cycle, plants_watering, plants
WHERE watering_cycle.id = plants_watering.watering_id
AND plants_watering.plant_id = plants.id
AND days > 7;

-- Displays plays that like more acidic soil -- 
SELECT plants.genus, plants.species, plants.common_name
FROM soil, plants_soil, plants
WHERE soil.id = plants_soil.soil_id
AND plants_soil.plant_id = plants.id
AND soil_ph <= 7;

-- Displays plantss that like more basic soil --
SELECT plants.genus, plants.species, plants.common_name
FROM soil, plants_soil, plants
WHERE soil.id = plants_soil.soil_id
AND plants_soil.plant_id = plants.id
AND soil_ph > 7;