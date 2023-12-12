CREATE DATABASE  IF NOT EXISTS `airline` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `airline`;
-- MySQL dump 10.13  Distrib 8.0.34, for macos13 (arm64)
--
-- Host: localhost    Database: airline
-- ------------------------------------------------------
-- Server version	8.1.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `aircraft`
--

DROP TABLE IF EXISTS `aircraft`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `aircraft` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `manufacturer` varchar(50) NOT NULL,
  `icaoCode` varchar(5) NOT NULL,
  `model` varchar(50) NOT NULL,
  `engineClass` enum('Piston','Jet','Turboprop') NOT NULL DEFAULT 'Turboprop',
  `numEngine` int NOT NULL DEFAULT '1',
  `numSeat` int NOT NULL DEFAULT '10',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `aircraft`
--

LOCK TABLES `aircraft` WRITE;
/*!40000 ALTER TABLE `aircraft` DISABLE KEYS */;
INSERT INTO `aircraft` VALUES (1,'Acro Sport','ACRO','Acro Sport','Piston',1,10),(2,'Adam Aircraft Industries','A500','A-500','Piston',2,20),(3,'Beechcraft','B18T','Model 18 Turboliner','Turboprop',2,40),(4,'Boeing','B743','747-300SR','Jet',4,75),(5,'Cessna','C526','CitationJet','Jet',2,50),(6,'Embraer','E170','EMB 175-E2','Jet',2,30),(7,'Globe Aircraft/TEMCO','GC1','GC-1B Globe','Piston',1,40),(8,'Israel Aircraft Industries','WW23','1123 Westwind','Jet',4,60),(9,'North American Rockwell','SBR1','Sabre 40/60','Jet',2,50),(10,'Piper','PA18','PA-18-150 Super Cub','Piston',1,30);
/*!40000 ALTER TABLE `aircraft` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `airlinemanifestview`
--

DROP TABLE IF EXISTS `airlinemanifestview`;
/*!50001 DROP VIEW IF EXISTS `airlinemanifestview`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `airlinemanifestview` AS SELECT 
 1 AS `Name`,
 1 AS `Phone Number`,
 1 AS `Role`,
 1 AS `Origin`,
 1 AS `Departure`,
 1 AS `Destination`,
 1 AS `Arrival`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `airport`
--

DROP TABLE IF EXISTS `airport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `airport` (
  `faa` char(3) NOT NULL,
  `icao` char(4) NOT NULL,
  `cityServed` char(5) NOT NULL,
  PRIMARY KEY (`faa`),
  UNIQUE KEY `icao` (`icao`),
  KEY `cityServed` (`cityServed`),
  CONSTRAINT `airport_ibfk_1` FOREIGN KEY (`cityServed`) REFERENCES `cityState` (`zipCode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `airport`
--

LOCK TABLES `airport` WRITE;
/*!40000 ALTER TABLE `airport` DISABLE KEYS */;
INSERT INTO `airport` VALUES ('DAB','KDAB','32114'),('ECP','KECP','32401'),('EYW','KEYW','33041'),('FLL','KFLL','33301'),('GNV','KGNV','32601'),('JAX','KJAX','32099'),('MCO','KMCO','32801'),('MIA','KMIA','33109'),('MLB','KMLB','32904'),('PBI','KPBI','33401'),('PGD','KPGD','33950'),('PIE','KPIE','33701'),('PNS','KPNS','32501'),('RSW','KRSW','33900'),('SFB','KSFB','32771'),('SRQ','KSRQ','34231'),('TLH','KTLH','32301'),('TPA','KTPA','33602'),('VPS','KVPS','32547');
/*!40000 ALTER TABLE `airport` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cityState`
--

DROP TABLE IF EXISTS `cityState`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cityState` (
  `city` varchar(90) NOT NULL,
  `state` char(2) NOT NULL,
  `zipCode` char(5) NOT NULL,
  PRIMARY KEY (`zipCode`),
  UNIQUE KEY `zipCode` (`zipCode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cityState`
--

LOCK TABLES `cityState` WRITE;
/*!40000 ALTER TABLE `cityState` DISABLE KEYS */;
INSERT INTO `cityState` VALUES ('Ballston Spa','NY','12020'),('Havertown','PA','19083'),('Waldorf','MD','20601'),('Glenarden','MD','20706'),('Chesterfield','VA','23832'),('Abingdon','VA','24210'),('Indian Trail','NC','28079'),('Mooresville','NC','28115'),('Clover','SC','29710'),('Duluth','GA','30096'),('Jacksonville','FL','32099'),('Daytona Beach','FL','32114'),('Tallahassee','FL','32301'),('Panama City','FL','32401'),('Pensacola','FL','32501'),('Fort Walton Beach','FL','32547'),('Gainesville','FL','32601'),('Sanford','FL','32771'),('Orlando','FL','32801'),('Melbourne','FL','32904'),('Key West','FL','33041'),('Miami','FL','33109'),('Fort Lauderdale','FL','33301'),('West Palm Beach','FL','33401'),('Jupiter','FL','33458'),('Tampa','FL','33602'),('St. Petersburg','FL','33701'),('Fort Myers','FL','33900'),('Punta Gorda','FL','33950'),('Sarasota','FL','34231'),('Nashville','TN','37205'),('Memphis','TN','38117'),('Vicksburg','MS','39180'),('Willoughby','OH','44094'),('Cuyahoga Falls','OH','44223'),('Chillicothe','OH','45601'),('Noblesville','IN','46060'),('Battle Creek','MI','49016'),('Trumbull','CT','6611'),('Jefferson','LA','70121'),('Covington','LA','70433'),('Paterson','NJ','7501'),('Scottsdale','AZ','85260'),('Piscataway','NJ','8854'),('Ontario','CA','91764'),('San Marcos','CA','92078'),('Huntington Beach','CA','92647'),('Santa Cruz','CA','95060');
/*!40000 ALTER TABLE `cityState` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employee` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `firstName` varchar(50) NOT NULL,
  `lastName` varchar(50) NOT NULL,
  `address` varchar(90) NOT NULL,
  `zipCode` char(5) NOT NULL,
  `phone` char(10) NOT NULL,
  `email` varchar(90) NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `phone` (`phone`),
  UNIQUE KEY `email` (`email`),
  KEY `zipCode` (`zipCode`),
  CONSTRAINT `employee_ibfk_1` FOREIGN KEY (`zipCode`) REFERENCES `cityState` (`zipCode`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (1,'Paris','Lindsey','763 West Mulberry St','29710','2025550132','plindsey@airline.com'),(2,'Umaiza','Melia','545 Ohio Ave','29710','2025550135','umelia@airline.com'),(3,'Nico','Prince','20 Middle River Street','44094','2025550137','nprince@airline.com'),(4,'Javan','Rennie','8112 North Country St','44094','2025550139','jrennie@airline.com'),(5,'Ali','Waters','83 Rockland Lane','44094','2025550144','awaters@airline.com'),(6,'JohnPaul','Clarke','1 Riverside Lane','44094','2025550153','jpcClarke@airline.com'),(7,'Dane','Kaiser','694 Wall Road','44094','2025550155','kdaiser@airline.com'),(8,'Hammad','Newman','9970 State Court','30096','2025550157','hnewman@airline.com'),(9,'Maha','Guthrie','54 Woodsman Drive','30096','2025550161','mguthrie@airline.com'),(10,'Tulisa','Roberts','7174 Studebaker Street','30096','2025550163','troberts@airline.com'),(11,'Raheem','Montgomery','71 Paris Hill Rd.','39180','4134849795','rmontgomery@airline.com'),(12,'Leo','Bird','201 Eagle Dr.','12020','7747829407','lbird@airline.com'),(13,'Oliwier','Barnett','81 Cedar Swamp St.','39180','2764343958','obarnett@airline.com'),(14,'Fern','Garner','37 Gartner Court','12020','2256254378','fgarner@airline.com'),(15,'Dawson','Marquez','90 Mammoth Street','45601','7634882879','dmarquez@airline.com'),(16,'Raja','Glass','7918 Talbot Ave.','45601','2319969540','rglass@airline.com'),(17,'Alissa','Ortiz','7756 Fulton Court','23832','2397268929','aortiz@airline.com'),(18,'Nicholas','Pena','8123 Race Ave.','95060','7815242242','npena@airline.com'),(19,'Harvey','West','9 Cherry Ave','23832','7326232762','hwest@airline.com'),(20,'Aamina','Dillon','9 West Boston Lane','95060','2035745299','adillon@airline.com'),(21,'Louis','Giles','598 North Road','28115','2708583758','lgiles@airline.com'),(22,'Krystal','Walters','583 North Nichols Street','95060','3232591832','kwalters@airline.com'),(23,'Alexa','Preston','9227 North Bow Ridge Street','28115','4098496634','apreston@airline.com'),(24,'Rebekah','Morgan','9437 East 6th Street','20601','6073928343','rmorgan@airline.com'),(25,'Ethan','Ali','167 NE. Depot Dr.','28115','2245499884','eali@airline.com'),(26,'Malik','Vincent','312 Colonial Ave.','19083','9149573014','mvincent@airline.com'),(27,'Sara','Barron','9064 E. Swanson St.','20601','8707743244','sbarron@airline.com'),(28,'Lyra','Murphy','400 Nut Swamp Drive','19083','3527673126','lmurphy@airline.com'),(29,'Awais','Carrillo','225 South Manhattan Street','28079','6369577670','acarrillo@airline.com'),(30,'Kaya','Hodge','9572 William Lane','46060','2125271561','khodge@airline.com'),(31,'Jemima','Miller','9290 Indian Spring Rd.','28079','6206673264','jmiller@airline.com'),(32,'Laila','Christensen','15 Rose Avenue','7501','9017396978','lchristensen@airline.com'),(33,'Honey','Warren','7946 Leeton Ridge Street','6611','5858531050','hwarren@airline.com'),(34,'Brodie','Gordon','71 Jackson Ave.','46060','9016899813','bgordon@airline.com'),(35,'Lauren','Morton','7931 Rockaway Street','28079','4476721422','lmorton@airline.com'),(36,'Ty','Bell','921 Brook St.','7501','2393336881','tbell@airline.com'),(37,'Floyd','Johns','2 Shore Street','6611','4065842872','fjohns@airline.com'),(38,'Mathew','Horton','1 Rockland Ave.','46060','7195789907','mhorton@airline.com'),(39,'Ernest','Higgins','451 Marshall Lane','6611','7637651247','ehiggins@airline.com'),(40,'Kamil','Lozano','75 N. Golden Star Street','7501','7638554744','klozano@airline.com'),(41,'Fatima','Robles','2519 Bottom Lane','33900','5126024452','frobles@airline.com'),(42,'Angelita','Turner','3447 Valley Lane','33109','8574960348','aturner@airline.com'),(43,'Robert','Johnson','526 Metz Lane','32401','5306942786','rjohnson@airline.com'),(44,'Francisca','Spence','1253 Coulter Lane','32547','8043389754','fspence@airline.com'),(45,'Matthew','Lee','756 Long Street','32601','3522635642','mlee@airline.com');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_employee_insert` AFTER INSERT ON `employee` FOR EACH ROW BEGIN
    INSERT INTO timesheet (employeeId, sun, mon, tues, wed, thurs, fri, sat)
    VALUES (NEW.id, 0, 0, 0, 0, 0, 0, 0);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `before_employee_update` BEFORE UPDATE ON `employee` FOR EACH ROW BEGIN
    INSERT INTO employeeAudit (action, employeeNumber, firstName, lastName, email, changeDate)
    VALUES ('UPDATE', OLD.id, OLD.firstName, OLD.lastName, OLD.email, NOW());
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `employeeAudit`
--

DROP TABLE IF EXISTS `employeeAudit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employeeAudit` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `employeeNumber` int NOT NULL,
  `firstName` varchar(50) NOT NULL,
  `lastName` varchar(50) NOT NULL,
  `email` varchar(90) NOT NULL,
  `changeDate` datetime DEFAULT NULL,
  `action` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=87 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employeeAudit`
--

LOCK TABLES `employeeAudit` WRITE;
/*!40000 ALTER TABLE `employeeAudit` DISABLE KEYS */;
INSERT INTO `employeeAudit` VALUES (1,1,'Paris','Lindsey','plindsey@isp.com','2023-12-03 00:43:08','UPDATE'),(2,2,'Umaiza','Melia','umelia@isp.com','2023-12-03 00:43:08','UPDATE'),(3,3,'Nico','Prince','nprince@isp.com','2023-12-03 00:43:08','UPDATE'),(4,4,'Javan','Rennie','jrennie@isp.com','2023-12-03 00:43:08','UPDATE'),(5,5,'Ali','Waters','awaters@isp.com','2023-12-03 00:43:08','UPDATE'),(6,6,'JohnPaul','Clarke','jpcClarke@isp.com','2023-12-03 00:43:08','UPDATE'),(7,7,'Dane','Kaiser','kdaiser@isp.com','2023-12-03 00:43:08','UPDATE'),(8,8,'Hammad','Newman','hnewman@isp.com','2023-12-03 00:43:08','UPDATE'),(9,9,'Maha','Guthrie','mguthrie@isp.com','2023-12-03 00:43:08','UPDATE'),(10,10,'Tulisa','Roberts','troberts@isp.com','2023-12-03 00:43:08','UPDATE'),(11,11,'Raheem','Montgomery','rmontgomery@cruise.com','2023-12-03 00:43:08','UPDATE'),(12,12,'Leo','Bird','lbird@cruise.com','2023-12-03 00:43:08','UPDATE'),(13,13,'Oliwier','Barnett','obarnett@cruise.com','2023-12-03 00:43:08','UPDATE'),(14,14,'Fern','Garner','fgarner@cruise.com','2023-12-03 00:43:08','UPDATE'),(15,15,'Dawson','Marquez','dmarquez@cruise.com','2023-12-03 00:43:08','UPDATE'),(16,16,'Raja','Glass','rglass@cruise.com','2023-12-03 00:43:08','UPDATE'),(17,17,'Alissa','Ortiz','aortiz@cruise.com','2023-12-03 00:43:08','UPDATE'),(18,18,'Nicholas','Pena','npena@cruise.com','2023-12-03 00:43:08','UPDATE'),(19,19,'Harvey','West','hwest@cruise.com','2023-12-03 00:43:08','UPDATE'),(20,20,'Aamina','Dillon','adillon@cruise.com','2023-12-03 00:43:08','UPDATE'),(21,21,'Louis','Giles','lgiles@cruise.com','2023-12-03 00:43:08','UPDATE'),(22,22,'Krystal','Walters','kwalters@cruise.com','2023-12-03 00:43:08','UPDATE'),(23,23,'Alexa','Preston','apreston@cruise.com','2023-12-03 00:43:08','UPDATE'),(24,24,'Rebekah','Morgan','rmorgan@cruise.com','2023-12-03 00:43:08','UPDATE'),(25,25,'Ethan','Ali','eali@cruise.com','2023-12-03 00:43:08','UPDATE'),(26,26,'Malik','Vincent','mvincent@cruise.com','2023-12-03 00:43:08','UPDATE'),(27,27,'Sara','Barron','sbarron@cruise.com','2023-12-03 00:43:08','UPDATE'),(28,28,'Lyra','Murphy','lmurphy@cruise.com','2023-12-03 00:43:08','UPDATE'),(29,29,'Awais','Carrillo','acarrillo@cruise.com','2023-12-03 00:43:08','UPDATE'),(30,30,'Kaya','Hodge','khodge@cruise.com','2023-12-03 00:43:08','UPDATE'),(31,31,'Jemima','Miller','jmiller@cruise.com','2023-12-03 00:43:08','UPDATE'),(32,32,'Laila','Christensen','lchristensen@cruise.com','2023-12-03 00:43:08','UPDATE'),(33,33,'Honey','Warren','hwarren@cruise.com','2023-12-03 00:43:08','UPDATE'),(34,34,'Brodie','Gordon','bgordon@cruise.com','2023-12-03 00:43:08','UPDATE'),(35,35,'Lauren','Morton','lmorton@cruise.com','2023-12-03 00:43:08','UPDATE'),(36,36,'Ty','Bell','tbell@cruise.com','2023-12-03 00:43:08','UPDATE'),(37,37,'Floyd','Johns','fjohns@cruise.com','2023-12-03 00:43:08','UPDATE'),(38,38,'Mathew','Horton','mhorton@cruise.com','2023-12-03 00:43:08','UPDATE'),(39,39,'Ernest','Higgins','ehiggins@cruise.com','2023-12-03 00:43:08','UPDATE'),(40,40,'Kamil','Lozano','klozano@cruise.com','2023-12-03 00:43:08','UPDATE'),(41,41,'Fatima','Robles','frobles@airline.com','2023-12-03 00:43:08','UPDATE'),(42,42,'Angelita','Turner','aturner@airline.com','2023-12-03 00:43:08','UPDATE'),(43,43,'Robert','Johnson','rjohnson@airline.com','2023-12-03 00:43:08','UPDATE'),(44,44,'Francisca','Spence','fspence@airline.com','2023-12-03 00:43:08','UPDATE'),(45,45,'Matthew','Lee','mlee@airline.com','2023-12-03 00:43:08','UPDATE');
/*!40000 ALTER TABLE `employeeAudit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employeeFlight`
--

DROP TABLE IF EXISTS `employeeFlight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employeeFlight` (
  `employeeID` int NOT NULL,
  `flightID` int NOT NULL,
  PRIMARY KEY (`employeeID`,`flightID`),
  KEY `flightID` (`flightID`),
  CONSTRAINT `employeeflight_ibfk_1` FOREIGN KEY (`employeeID`) REFERENCES `employee` (`ID`),
  CONSTRAINT `employeeflight_ibfk_2` FOREIGN KEY (`flightID`) REFERENCES `flight` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employeeFlight`
--

LOCK TABLES `employeeFlight` WRITE;
/*!40000 ALTER TABLE `employeeFlight` DISABLE KEYS */;
INSERT INTO `employeeFlight` VALUES (2,100),(3,100),(24,100),(34,100),(36,100),(12,106),(26,106),(28,106),(32,106),(38,106),(1,113),(3,113),(14,113),(26,113),(36,113),(12,116),(24,116),(28,116),(32,116),(34,116);
/*!40000 ALTER TABLE `employeeFlight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `employeeflightview`
--

DROP TABLE IF EXISTS `employeeflightview`;
/*!50001 DROP VIEW IF EXISTS `employeeflightview`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `employeeflightview` AS SELECT 
 1 AS `Employee`,
 1 AS `Origin`,
 1 AS `Departure`,
 1 AS `Destination`,
 1 AS `Arrival`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `employeePosition`
--

DROP TABLE IF EXISTS `employeePosition`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employeePosition` (
  `employeeID` int NOT NULL,
  `positionID` int NOT NULL,
  PRIMARY KEY (`employeeID`,`positionID`),
  UNIQUE KEY `employeeID` (`employeeID`),
  KEY `positionID` (`positionID`),
  CONSTRAINT `employeeposition_ibfk_1` FOREIGN KEY (`employeeID`) REFERENCES `employee` (`ID`),
  CONSTRAINT `employeeposition_ibfk_2` FOREIGN KEY (`positionID`) REFERENCES `position` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employeePosition`
--

LOCK TABLES `employeePosition` WRITE;
/*!40000 ALTER TABLE `employeePosition` DISABLE KEYS */;
INSERT INTO `employeePosition` VALUES (1,1),(2,2),(3,3),(4,6),(5,7),(6,11),(7,14),(8,15),(9,15),(10,16),(11,8),(12,2),(13,12),(14,2),(15,13),(16,17),(17,6),(18,4),(19,6),(20,9),(21,17),(22,10),(23,17),(24,3),(25,17),(26,3),(27,15),(28,3),(29,15),(30,5),(31,15),(32,3),(33,8),(34,1),(35,8),(36,3),(37,11),(38,1),(39,14),(40,6);
/*!40000 ALTER TABLE `employeePosition` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `flight`
--

DROP TABLE IF EXISTS `flight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `flight` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `origin` char(3) NOT NULL,
  `destination` char(3) NOT NULL,
  `aircraft` int NOT NULL,
  `departure` timestamp NOT NULL,
  `arrival` timestamp NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `origin` (`origin`),
  KEY `destination` (`destination`),
  KEY `aircraft` (`aircraft`),
  CONSTRAINT `flight_ibfk_1` FOREIGN KEY (`origin`) REFERENCES `airport` (`faa`),
  CONSTRAINT `flight_ibfk_2` FOREIGN KEY (`destination`) REFERENCES `airport` (`faa`),
  CONSTRAINT `flight_ibfk_3` FOREIGN KEY (`aircraft`) REFERENCES `aircraft` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=119 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `flight`
--

LOCK TABLES `flight` WRITE;
/*!40000 ALTER TABLE `flight` DISABLE KEYS */;
INSERT INTO `flight` VALUES (100,'DAB','FLL',1,'2023-11-01 11:00:00','2023-11-01 12:00:00'),(101,'FLL','RSW',9,'2023-11-01 12:00:00','2023-11-01 13:00:00'),(102,'RSW','VPS',2,'2023-11-01 13:00:00','2023-11-01 14:00:00'),(103,'VPS','GNV',8,'2023-11-01 14:00:00','2023-11-01 15:00:00'),(104,'GNV','JAX',3,'2023-11-11 16:00:00','2023-11-11 17:00:00'),(105,'JAX','EYW',7,'2023-11-11 17:00:00','2023-11-11 18:00:00'),(106,'EYW','MLB',4,'2023-11-04 17:00:00','2023-11-04 18:00:00'),(107,'MLB','MIA',6,'2023-11-04 18:00:00','2023-11-04 19:00:00'),(108,'MIA','MCO',5,'2023-11-05 20:00:00','2023-11-05 21:00:00'),(109,'MCO','ECP',5,'2023-11-05 21:00:00','2023-11-05 22:00:00'),(110,'ECP','PNS',6,'2023-11-06 22:00:00','2023-11-06 23:00:00'),(111,'PNS','PGD',4,'2023-11-07 00:00:00','2023-11-07 01:00:00'),(112,'PGD','SFB',7,'2023-11-07 12:00:00','2023-11-07 13:00:00'),(113,'SFB','SRQ',3,'2023-11-07 14:00:00','2023-11-07 15:00:00'),(114,'SRQ','PIE',8,'2023-11-08 12:00:00','2023-11-08 13:00:00'),(115,'PIE','TLH',2,'2023-11-08 14:00:00','2023-11-08 15:00:00'),(116,'TLH','TPA',9,'2023-11-09 12:00:00','2023-11-09 13:00:00'),(117,'TPA','PBI',1,'2023-11-09 15:00:00','2023-11-09 16:00:00'),(118,'PBI','DAB',10,'2023-11-10 16:00:00','2023-11-10 17:00:00');
/*!40000 ALTER TABLE `flight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `passenger`
--

DROP TABLE IF EXISTS `passenger`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `passenger` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `firstName` varchar(50) NOT NULL,
  `lastName` varchar(50) NOT NULL,
  `address` varchar(90) NOT NULL,
  `zipCode` char(5) NOT NULL,
  `phone` char(10) NOT NULL,
  `email` varchar(90) NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `phone` (`phone`),
  UNIQUE KEY `email` (`email`),
  KEY `zipCode` (`zipCode`),
  CONSTRAINT `passenger_ibfk_1` FOREIGN KEY (`zipCode`) REFERENCES `cityState` (`zipCode`)
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `passenger`
--

LOCK TABLES `passenger` WRITE;
/*!40000 ALTER TABLE `passenger` DISABLE KEYS */;
INSERT INTO `passenger` VALUES (1,'Igor','Prince','12 Creekside St','92647','2025550199','iprince@isp.com'),(2,'Dante','Rennie','137 Wall St','38117','2225550112','drennie@isp.com'),(3,'Thomas','Waters','411 Shirley St','24210','2225550115','twaters@isp.com'),(4,'Avaya','Clarke','7771 Border Court','92078','2225550119','aclarke@isp.com'),(5,'Haniya','Kaiser','6 South Sulphur Springs Street','70121','2225550121','hkaiser@isp.com'),(6,'Victor','Newman','942 New Saddle Drive','70433','2225550122','vnewman@isp.com'),(7,'Douglas','Guthrie','9 Wrangler Ave','91764','2225550124','dguthrie@isp.com'),(8,'Brian','Roberts','7319 S. Greenview Drive','44223','2225550125','broberts@isp.com'),(9,'Paris','Solis','763 West Mulberry St','49016','2025550132','psolis@isp.com'),(10,'Umaiza','Heath','545 Ohio Ave','85260','2025550135','uheath@isp.com'),(11,'Yvonne','Goodman','12 Creekside St','37205','2025550109','ygoodman@isp.com'),(12,'Dante','Mackenzie','137 Wall St','37205','2025550112','dmackenzie@isp.com'),(13,'Alysha','Rollins','411 Shirley St','37205','2025550115','arollins@isp.com'),(14,'Avaya','Gonzalez','7771 Border Court','37205','2025550119','agonzalez@isp.com'),(15,'Haniya','Kelly','6 South Sulphur Springs Street','37205','2025550121','hkelly@isp.com'),(16,'Nathalie','Chambers','942 New Saddle Drive','29710','2025550122','nchambers@isp.com'),(17,'Dante','Rollins','9 Wrangler Ave','29710','2025550124','drollins@isp.com'),(18,'Beverley','Mckee','7319 S. Greenview Drive','29710','2025550125','bmckee@isp.com'),(19,'Robin','Solis','8474 Wentworth Street','30096','2025550164','rsolis@isp.com'),(20,'Kavita','Heath','796 Hartford St','30096','2025550165','kheath@isp.com'),(21,'Meera','White','484 Bridge St','8854','2025550166','mwhite@isp.com'),(22,'Bradlee','Esparza','7031 Gainsway St','8854','2025550173','besparza@isp.com'),(23,'Leilani','Leonard','37 Monroe Street','8854','2025550175','lleonard@isp.com'),(24,'Stefanie','Brook','7990 West Surrey St','8854','2025550179','sbrook@isp.com'),(25,'Grover','Squires','7618 Madison Court','8854','2025550180','gsquires@isp.com'),(26,'Jonathan','Kumar','25 Annadale Court','33458','2025550182','jkumar@isp.com'),(27,'Angus','Neville','9841 Smith Drive','33458','2025550187','aneville@isp.com'),(28,'Uzair','Sparrow','7999 Hall Street','33458','2025550188','usparrow@isp.com'),(29,'Amari','Currie','8411 Pleasant St','33458','2025550194','acurrie@isp.com'),(30,'Imaani','Wallace','33 Pierce Rd','33458','2025550195','iwallace@isp.com'),(31,'Efe','House','97 High Point Street','20706','2025550196','ehouse@isp.com'),(32,'Atticus','Atkinson','66 Harrison Dr','20706','2025550197','aatkinson@isp.com'),(33,'Michelle','Ramirez','370 Hill Field Ave','20706','2025550198','mramirez@isp.com'),(34,'Remy','Hassan','249 Devon Lane','20706','2225550199','rhassan@isp.com'),(35,'Jordana','Beck','7911 Carson Lane','20706','2025550200','jbeck@isp.com');
/*!40000 ALTER TABLE `passenger` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `passengerFlight`
--

DROP TABLE IF EXISTS `passengerFlight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `passengerFlight` (
  `passengerID` int NOT NULL,
  `flightID` int NOT NULL,
  PRIMARY KEY (`passengerID`,`flightID`),
  KEY `flightID` (`flightID`),
  CONSTRAINT `passengerflight_ibfk_1` FOREIGN KEY (`passengerID`) REFERENCES `passenger` (`ID`),
  CONSTRAINT `passengerflight_ibfk_2` FOREIGN KEY (`flightID`) REFERENCES `flight` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `passengerFlight`
--

LOCK TABLES `passengerFlight` WRITE;
/*!40000 ALTER TABLE `passengerFlight` DISABLE KEYS */;
INSERT INTO `passengerFlight` VALUES (2,100),(3,100),(13,100),(19,100),(35,100),(4,106),(5,106),(25,106),(30,106),(33,106),(6,113),(10,113),(11,113),(20,113),(31,113),(1,116),(8,116),(14,116),(18,116),(29,116);
/*!40000 ALTER TABLE `passengerFlight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `passengerflightview`
--

DROP TABLE IF EXISTS `passengerflightview`;
/*!50001 DROP VIEW IF EXISTS `passengerflightview`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `passengerflightview` AS SELECT 
 1 AS `Passenger`,
 1 AS `Origin`,
 1 AS `Departure`,
 1 AS `Destination`,
 1 AS `Arrival`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `position`
--

DROP TABLE IF EXISTS `position`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `position` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `description` varchar(50) NOT NULL,
  `hourly` decimal(5,2) NOT NULL DEFAULT '11.00',
  PRIMARY KEY (`ID`),
  UNIQUE KEY `description` (`description`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `position`
--

LOCK TABLES `position` WRITE;
/*!40000 ALTER TABLE `position` DISABLE KEYS */;
INSERT INTO `position` VALUES (1,'Pilot',58.00),(2,'Co-pilot',40.00),(3,'Flight Attendant',48.00),(4,'Cabin Attendant',38.00),(5,'Aeronautical Engineer',42.00),(6,'Aircraft Mechanic',33.00),(7,'Airport Police',20.00),(8,'Security',14.00),(9,'Airport Planner',46.00),(10,'Airfield Operations Specialists',22.00),(11,'Airline Ticket Agent',13.00),(12,'Reservation Service Agent',15.00),(13,'Passenger Service Agent',11.00),(14,'Meteorologist',37.00),(15,'Baggage Handler',13.00),(16,'Administrative Jobs',17.00),(17,'Cleaning Jobs',13.00);
/*!40000 ALTER TABLE `position` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `timesheet`
--

DROP TABLE IF EXISTS `timesheet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `timesheet` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `employeeID` int NOT NULL,
  `sun` int NOT NULL DEFAULT '0',
  `mon` int NOT NULL DEFAULT '0',
  `tues` int NOT NULL DEFAULT '0',
  `wed` int NOT NULL DEFAULT '0',
  `thurs` int NOT NULL DEFAULT '0',
  `fri` int NOT NULL DEFAULT '0',
  `sat` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`),
  KEY `employeeID` (`employeeID`),
  CONSTRAINT `timesheet_ibfk_1` FOREIGN KEY (`employeeID`) REFERENCES `employee` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `timesheet`
--

LOCK TABLES `timesheet` WRITE;
/*!40000 ALTER TABLE `timesheet` DISABLE KEYS */;
INSERT INTO `timesheet` VALUES (1,25,7,4,9,0,0,10,3),(2,13,0,12,6,10,6,8,0),(3,27,10,8,0,0,8,10,10),(4,36,12,0,12,0,4,12,0),(5,12,6,6,6,6,6,5,0),(6,29,12,0,12,0,4,12,0),(7,32,12,0,12,0,4,12,0),(8,6,12,0,12,0,4,12,0),(9,20,7,4,9,0,0,10,3),(10,14,0,12,6,10,6,8,0),(11,21,6,6,6,6,6,5,0),(12,16,0,8,8,8,8,8,0),(13,34,6,6,6,6,6,5,0),(14,9,10,8,0,0,8,10,10),(15,39,0,8,8,8,8,8,0),(16,30,0,12,6,10,6,8,0),(17,38,6,6,6,6,6,5,0),(18,37,0,8,8,8,8,8,0),(19,7,8,8,0,0,8,10,6),(20,1,10,8,0,0,8,10,10),(21,40,10,8,0,0,8,10,10),(22,15,12,0,12,0,4,12,0),(23,2,8,8,0,0,8,10,6),(24,31,10,8,0,0,8,10,10),(25,11,0,8,8,8,8,8,0),(26,24,6,6,6,6,6,5,0),(27,35,7,4,9,0,0,10,3),(28,28,0,12,6,10,6,8,0),(29,8,0,8,8,8,8,8,0),(30,17,0,8,8,8,8,8,0),(31,18,8,8,0,0,8,10,6),(32,23,0,12,6,10,6,8,0),(33,3,6,6,6,6,6,5,0),(34,4,7,4,9,0,0,10,3),(35,10,10,8,0,0,8,10,10),(36,26,0,12,6,10,6,8,0),(37,22,8,8,0,0,8,10,6),(38,33,8,8,0,0,8,10,6),(39,5,0,8,8,8,8,8,0),(40,19,12,0,12,0,4,12,0),(41,41,0,0,0,0,0,0,0),(42,42,0,0,0,0,0,0,0),(43,43,0,0,0,0,0,0,0),(44,44,0,0,0,0,0,0,0),(45,45,0,0,0,0,0,0,0);
/*!40000 ALTER TABLE `timesheet` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `timesheetview`
--

DROP TABLE IF EXISTS `timesheetview`;
/*!50001 DROP VIEW IF EXISTS `timesheetview`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `timesheetview` AS SELECT 
 1 AS `Employee`,
 1 AS `Position`,
 1 AS `Hours`*/;
SET character_set_client = @saved_cs_client;

--
-- Dumping events for database 'airline'
--

--
-- Dumping routines for database 'airline'
--
/*!50003 DROP PROCEDURE IF EXISTS `payDeposit` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `payDeposit`(
    IN employeeNum INT,
    INOUT deposit VARCHAR(4000)
)
BEGIN
    
    DECLARE v_finished INT DEFAULT 0;
    DECLARE v_lines VARCHAR(100) DEFAULT "--------------------------------------------------------------------------------";
    DECLARE v_empFirst VARCHAR(100) DEFAULT "";
    DECLARE v_empLast VARCHAR(100) DEFAULT "";
    DECLARE v_empAddress VARCHAR(100) DEFAULT "";
    DECLARE v_empCity VARCHAR(100) DEFAULT "";
    DECLARE v_empState VARCHAR(100) DEFAULT "";
    DECLARE v_empZip VARCHAR(100) DEFAULT "";
    DECLARE v_tHours INT DEFAULT 0;
    DECLARE v_pHourly DECIMAL(5,2) DEFAULT 0.0;
    DECLARE v_overtime INT DEFAULT 0;
    DECLARE v_count INT DEFAULT 0;
    DECLARE v_deposit DECIMAL(8,2) DEFAULT 0.0;

    
    DECLARE employee_cursor CURSOR FOR
        SELECT
            e.firstName,
            e.lastName,
            e.address,
            cs.city,
            cs.state,
            cs.zipCode,
            SUM(t.sun+t.mon+t.tues+t.wed+t.thurs+t.fri+t.sat) AS "hours",
            p.hourly
        FROM
            employee e
            JOIN cityState AS cs ON e.zipCode = cs.zipCode
            JOIN timesheet AS t ON e.ID = t.employeeID
    JOIN employeePosition AS ep ON e.ID = ep.employeeID
            JOIN position AS p ON ep.positionID = p.ID
        WHERE
            e.ID = employeeNum
        GROUP BY
            e.firstName, e.lastName, e.address, cs.city, cs.state, cs.zipCode, p.hourly;

    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_finished = 1;

    
    OPEN employee_cursor;

    
    get_employee: LOOP
        FETCH employee_cursor INTO v_empFirst, v_empLast, v_empAddress, v_empCity, v_empState, v_empZip, v_tHours, v_pHourly;

        IF v_finished = 1 THEN
            LEAVE get_employee;
        END IF;

        SET v_count = v_count + 1;

        IF v_count = 1 THEN
            IF v_tHours <= 40 THEN
                SET v_deposit = v_tHours * v_pHourly;
            ELSE
                SET v_overtime = (v_tHours - 40) * (v_pHourly * 1.5);
                SET v_deposit = 40 * v_pHourly + v_overtime;
            END IF;

            
            SET deposit = CONCAT(
                deposit, 
                '\nFrom:\n\nCGS 2545 Regional Airlines \nUCF\nMSB 260\n\n',
                'Pay to the order of:\n\n',
                v_empFirst, ' ', v_empLast, '\n',
                v_empAddress, '\n',
                v_empCity, ', ', v_empState, ' ', v_empZip, '\n',
                '\nIn the amount of:\n\n$',
                v_deposit,
                '\n\n*** Pay will be deposited into account number provided ***\n',
                '\n', v_lines, '\n'
            );
        END IF;
    END LOOP;

    
    CLOSE employee_cursor;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Final view structure for view `airlinemanifestview`
--

/*!50001 DROP VIEW IF EXISTS `airlinemanifestview`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `airlinemanifestview` AS select concat(`e`.`firstName`,' ',`e`.`lastName`) AS `Name`,`e`.`phone` AS `Phone Number`,`p`.`description` AS `Role`,`f`.`origin` AS `Origin`,`f`.`departure` AS `Departure`,`f`.`destination` AS `Destination`,`f`.`arrival` AS `Arrival` from ((((`employee` `e` join `employeeflight` `ef` on((`e`.`ID` = `ef`.`employeeID`))) join `employeeposition` `ep` on((`e`.`ID` = `ep`.`employeeID`))) join `position` `p` on((`ep`.`positionID` = `p`.`ID`))) join `flight` `f` on((`ef`.`flightID` = `f`.`ID`))) union select concat(`p`.`firstName`,' ',`p`.`lastName`) AS `Name`,`p`.`phone` AS `Phone Number`,'Passenger' AS `Role`,`f`.`origin` AS `Origin`,`f`.`departure` AS `Departure`,`f`.`destination` AS `Destination`,`f`.`arrival` AS `Arrival` from ((`passenger` `p` join `passengerflight` `pf` on((`p`.`ID` = `pf`.`passengerID`))) join `flight` `f` on((`pf`.`flightID` = `f`.`ID`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `employeeflightview`
--

/*!50001 DROP VIEW IF EXISTS `employeeflightview`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `employeeflightview` AS select concat(`e`.`firstName`,' ',`e`.`lastName`) AS `Employee`,`f`.`origin` AS `Origin`,`f`.`departure` AS `Departure`,`f`.`destination` AS `Destination`,`f`.`arrival` AS `Arrival` from ((`employee` `e` join `employeeflight` `ef` on((`e`.`ID` = `ef`.`employeeID`))) join `flight` `f` on((`ef`.`flightID` = `f`.`ID`))) order by `f`.`departure`,`e`.`lastName` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `passengerflightview`
--

/*!50001 DROP VIEW IF EXISTS `passengerflightview`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `passengerflightview` AS select concat(`p`.`firstName`,' ',`p`.`lastName`) AS `Passenger`,`f`.`origin` AS `Origin`,`f`.`departure` AS `Departure`,`f`.`destination` AS `Destination`,`f`.`arrival` AS `Arrival` from ((`passenger` `p` join `passengerflight` `pf` on((`p`.`ID` = `pf`.`passengerID`))) join `flight` `f` on((`pf`.`flightID` = `f`.`ID`))) order by `f`.`departure`,`p`.`lastName` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `timesheetview`
--

/*!50001 DROP VIEW IF EXISTS `timesheetview`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `timesheetview` AS select concat(`e`.`firstName`,' ',`e`.`lastName`) AS `Employee`,`p`.`description` AS `Position`,((((((`t`.`sun` + `t`.`mon`) + `t`.`tues`) + `t`.`wed`) + `t`.`thurs`) + `t`.`fri`) + `t`.`sat`) AS `Hours` from (((`employee` `e` join `employeeposition` `ep` on((`e`.`ID` = `ep`.`employeeID`))) join `position` `p` on((`ep`.`positionID` = `p`.`ID`))) left join `timesheet` `t` on((`e`.`ID` = `t`.`employeeID`))) order by `e`.`lastName` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-06 19:31:22
