-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: classmysql.engr.oregonstate.edu:3306
-- Generation Time: May 12, 2019 at 08:34 PM
-- Server version: 10.3.13-MariaDB-log
-- PHP Version: 7.0.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

SET FOREIGN_KEY_CHECKS = 0;
DROP TABLE IF EXISTS `plants`;
DROP TABLE IF EXISTS `climate`;
DROP TABLE IF EXISTS `soil`;
DROP TABLE IF EXISTS `sunlight`;
DROP TABLE IF EXISTS `watering_cycle`;
DROP TABLE IF EXISTS `plants_watering`;
DROP TABLE IF EXISTS `plants_soil`;
SET FOREIGN_KEY_CHECKS = 1;


--
-- Database: `cs340_eckru`
--

-- --------------------------------------------------------

--
-- Table structure for table `climate`
--

CREATE TABLE `climate` (
  `id` int(11) NOT NULL,
  `lowest_temperature` int(11) NOT NULL,
  `highest_temperature` int(11) NOT NULL,
  `humidity` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `climate`
--

INSERT INTO `climate` (`id`, `lowest_temperature`, `highest_temperature`, `humidity`) VALUES
(1, 30, 90, 50),
(2, 30, 90, 40),
(3, 20, 80, 30),
(4, 15, 75, 20),
(5, 40, 80, 80),
(6, -5, 75, 0),
(7, 0, 68, 14),
(8, 10, 74, 24),
(9, 15, 93, 70),
(10, 22, 72, 55);

-- --------------------------------------------------------

--
-- Table structure for table `plants`
--

CREATE TABLE `plants` (
  `id` int(11) NOT NULL,
  `genus` varchar(75) NOT NULL,
  `species` varchar(75) NOT NULL,
  `common_name` varchar(75) DEFAULT NULL,
  `required_light` int(11) DEFAULT NULL,
  `climate_type` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `plants`
--

INSERT INTO `plants` (`id`, `genus`, `species`, `common_name`, `required_light`, `climate_type`) VALUES
(1, 'Peperomia', 'tetragona', 'Parallel Peperomia', 1, 1),
(2, 'Peperomia', 'prostrata', 'String of Turtles', 2, 4),
(3, 'Oxalis', 'triangularis', 'False Clover', 4, 1),
(4, 'Tradescantia', 'zebrina', 'Wandering Jew', 10, 3),
(5, 'Ceropegia', 'woodii', 'String of Hearts', 8, 6),
(6, 'Pilea', 'peperomioides', 'Chinese Money Plant', 9, 9),
(7, 'Monstera', 'deliciosa', 'Swiss Cheese Plant', 2, 7),
(8, 'Monstera', 'adansonii', 'Swiss Cheese Vine', 6, 6);

-- --------------------------------------------------------

--
-- Table structure for table `plants_soil`
--

CREATE TABLE `plants_soil` (
  `plant_id` int(11) NOT NULL DEFAULT 0,
  `soil_id` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `plants_soil`
--

INSERT INTO `plants_soil` (`plant_id`, `soil_id`) VALUES
(1, 5),
(1, 10),
(2, 2),
(3, 7),
(4, 5),
(5, 4),
(5, 5),
(6, 2),
(7, 8),
(8, 11);

-- --------------------------------------------------------

--
-- Table structure for table `plants_watering`
--

CREATE TABLE `plants_watering` (
  `plant_id` int(11) NOT NULL DEFAULT 0,
  `watering_id` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `plants_watering`
--

INSERT INTO `plants_watering` (`plant_id`, `watering_id`) VALUES
(1, 1),
(1, 2),
(1, 3),
(2, 4),
(3, 8),
(4, 9),
(5, 7),
(6, 9),
(7, 5),
(7, 8),
(8, 4);

-- --------------------------------------------------------

--
-- Table structure for table `soil`
--

CREATE TABLE `soil` (
  `id` int(11) NOT NULL,
  `soil_type` varchar(75) NOT NULL,
  `soil_ph` int(11) NOT NULL,
  `fertilizer` tinyint(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `soil`
--

INSERT INTO `soil` (`id`, `soil_type`, `soil_ph`, `fertilizer`) VALUES
(1, 'Sandy Loam', 7, 0),
(2, 'Sandy Loam', 7, 1),
(3, 'Sand', 7, 0),
(4, 'Sand', 7, 0),
(5, 'Peat', 8, 0),
(6, 'Peat', 7, 1),
(7, 'Clay', 6, 0),
(8, 'Clay', 7, 1),
(9, 'Loam', 7, 0),
(10, 'Loam', 6, 1),
(11, 'Silt', 8, 1),
(12, 'Chalky', 6, 0);

-- --------------------------------------------------------

--
-- Table structure for table `sunlight`
--

CREATE TABLE `sunlight` (
  `id` int(11) NOT NULL,
  `sunlight_hours` int(11) NOT NULL,
  `full_sunlight` tinyint(1) NOT NULL DEFAULT 0,
  `medium_sunlight` tinyint(1) NOT NULL DEFAULT 0,
  `low_sunlight` tinyint(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sunlight`
--

INSERT INTO `sunlight` (`id`, `sunlight_hours`, `full_sunlight`, `medium_sunlight`, `low_sunlight`) VALUES
(1, 12, 1, 1, 0),
(2, 10, 0, 1, 0),
(3, 14, 1, 0, 0),
(4, 13, 1, 0, 0),
(5, 7, 0, 1, 1),
(6, 10, 1, 1, 1),
(7, 9, 0, 1, 0),
(8, 10, 0, 1, 1),
(9, 11, 0, 1, 1),
(10, 6, 0, 0, 1);

-- --------------------------------------------------------

--
-- Table structure for table `watering_cycle`
--

CREATE TABLE `watering_cycle` (
  `id` int(11) NOT NULL,
  `days` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `watering_cycle`
--

INSERT INTO `watering_cycle` (`id`, `days`) VALUES
(1, 0),
(2, 1),
(3, 2),
(4, 3),
(5, 4),
(6, 5),
(7, 6),
(8, 7),
(9, 8),
(10, 9),
(11, 10),
(12, 11),
(13, 12),
(14, 13),
(15, 14);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `climate`
--
ALTER TABLE `climate`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `plants`
--
ALTER TABLE `plants`
  ADD PRIMARY KEY (`id`),
  ADD KEY `required_light` (`required_light`),
  ADD KEY `climate_type` (`climate_type`);

--
-- Indexes for table `plants_soil`
--
ALTER TABLE `plants_soil`
  ADD PRIMARY KEY (`plant_id`,`soil_id`),
  ADD KEY `plant_id` (`plant_id`),
  ADD KEY `soil_id` (`soil_id`);

--
-- Indexes for table `plants_watering`
--
ALTER TABLE `plants_watering`
  ADD PRIMARY KEY (`plant_id`,`watering_id`),
  ADD KEY `plant_id` (`plant_id`),
  ADD KEY `watering_id` (`watering_id`);

--
-- Indexes for table `soil`
--
ALTER TABLE `soil`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sunlight`
--
ALTER TABLE `sunlight`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `watering_cycle`
--
ALTER TABLE `watering_cycle`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `climate`
--
ALTER TABLE `climate`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `plants`
--
ALTER TABLE `plants`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `soil`
--
ALTER TABLE `soil`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT for table `sunlight`
--
ALTER TABLE `sunlight`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `watering_cycle`
--
ALTER TABLE `watering_cycle`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `plants`
--
ALTER TABLE `plants`
  ADD CONSTRAINT `plants_ibfk_1` FOREIGN KEY (`required_light`) REFERENCES `sunlight` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `plants_ibfk_2` FOREIGN KEY (`climate_type`) REFERENCES `climate` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `plants_soil`
--
ALTER TABLE `plants_soil`
  ADD CONSTRAINT `plants_soil_ibfk_1` FOREIGN KEY (`plant_id`) REFERENCES `plants` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `plants_soil_ibfk_2` FOREIGN KEY (`soil_id`) REFERENCES `soil` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `plants_watering`
--
ALTER TABLE `plants_watering`
  ADD CONSTRAINT `plants_watering_ibfk_1` FOREIGN KEY (`plant_id`) REFERENCES `plants` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `plants_watering_ibfk_2` FOREIGN KEY (`watering_id`) REFERENCES `watering_cycle` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
