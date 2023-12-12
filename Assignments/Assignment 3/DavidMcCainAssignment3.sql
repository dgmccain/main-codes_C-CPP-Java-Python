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
INSERT INTO `cityState` VALUES ('Glenarden','MD','20706'),('Abingdon','VA','24210'),('Clover','SC','29710'),('Duluth','GA','30096'),('Jupiter','FL','33458'),('Nashville','TN','37205'),('Memphis','TN','38117'),('Willoughby','OH','44094'),('Cuyahoga Falls','OH','44223'),('Battle Creek','MI','49016'),('Jefferson','LA','70121'),('Covington','LA','70433'),('Scottsdale','AZ','85260'),('Piscataway','NJ','8854'),('Ontario','CA','91764'),('San Marcos','CA','92078'),('Huntington Beach','CA','92647');
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
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (1,'Paris','Lindsey','763 West Mulberry St','29710','2025550132','plindsey@isp.com'),(2,'Umaiza','Melia','545 Ohio Ave','29710','2025550135','umelia@isp.com'),(3,'Nico','Prince','20 Middle River Street','44094','2025550137','nprince@isp.com'),(4,'Javan','Rennie','8112 North Country St','44094','2025550139','jrennie@isp.com'),(5,'Ali','Waters','83 Rockland Lane','44094','2025550144','awaters@isp.com'),(6,'JohnPaul','Clarke','1 Riverside Lane','44094','2025550153','jpcClarke@isp.com'),(7,'Dane','Kaiser','694 Wall Road','44094','2025550155','kdaiser@isp.com'),(8,'Hammad','Newman','9970 State Court','30096','2025550157','hnewman@isp.com'),(9,'Maha','Guthrie','54 Woodsman Drive','30096','2025550161','mguthrie@isp.com'),(10,'Tulisa','Roberts','7174 Studebaker Street','30096','2025550163','troberts@isp.com');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;

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
INSERT INTO `employeePosition` VALUES (1,1),(2,2),(3,3),(4,6),(5,7),(6,11),(7,14),(8,15),(9,15),(10,16);
/*!40000 ALTER TABLE `employeePosition` ENABLE KEYS */;
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
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-09-29 21:56:00
