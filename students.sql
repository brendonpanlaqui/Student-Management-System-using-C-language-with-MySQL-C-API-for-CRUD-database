-- MariaDB dump 10.19  Distrib 10.5.21-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: group1
-- ------------------------------------------------------
-- Server version	10.5.21-MariaDB-0+deb11u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Grades`
--

DROP TABLE IF EXISTS `Grades`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Grades` (
  `gradeID` int(11) NOT NULL AUTO_INCREMENT,
  `studNumbers` int(11) DEFAULT NULL,
  `subjectName` varchar(50) DEFAULT NULL,
  `grade` int(11) DEFAULT NULL,
  PRIMARY KEY (`gradeID`),
  KEY `studNumbers` (`studNumbers`),
  CONSTRAINT `Grades_ibfk_1` FOREIGN KEY (`studNumbers`) REFERENCES `Students` (`studNumbers`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Grades`
--

LOCK TABLES `Grades` WRITE;
/*!40000 ALTER TABLE `Grades` DISABLE KEYS */;
INSERT INTO `Grades` VALUES (1,230120,'Fundamentals of Programming',100),(2,230120,'Introduction to Computing',94),(3,230120,'Information Management',100),(4,230120,'Mathematics in the Modern World',100),(5,230120,'Purposive Communication',99),(6,230120,'Understanding the Self',94),(7,230120,'Physical Education',94),(8,230120,'National Service Training Program',93);
/*!40000 ALTER TABLE `Grades` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Students`
--

DROP TABLE IF EXISTS `Students`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Students` (
  `studNumbers` int(11) NOT NULL,
  `firstName` char(25) DEFAULT NULL,
  `lastName` char(25) DEFAULT NULL,
  `birthDate` varchar(25) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `cpNum` char(11) DEFAULT NULL,
  PRIMARY KEY (`studNumbers`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Students`
--

LOCK TABLES `Students` WRITE;
/*!40000 ALTER TABLE `Students` DISABLE KEYS */;
INSERT INTO `Students` VALUES (230053,'Kristine Angela','Zamora','05/08/2004','kristinegelatine@gmail.com','09349236235'),(230080,'Nikko','David','04/12/2004','davidnikko@yahoo.com','09958327589'),(230109,'Edcel','Wiyangco','01/30/2004','edcelwiyango@yahoo.com','09124820425'),(230120,'Brendon','Panlaqui','06/15/2005','arbetpanlaqui874@gmail.com','09946308962'),(230142,'Warren','Manalo','06/27/2005','manalowarren@gmail.com','09959238533'),(230178,'Sean Warren','Naguit','06/10/2005','seanwarrennaguit@gmail.com','09539243855');
/*!40000 ALTER TABLE `Students` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-16 21:37:16
