-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: 192.168.1.40    Database: modeo
-- ------------------------------------------------------
-- Server version	5.7.35-0ubuntu0.18.04.2

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
-- Table structure for table `cihazkimlik`
--

DROP TABLE IF EXISTS `cihazkimlik`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cihazkimlik` (
  `Sıra` int(11) NOT NULL AUTO_INCREMENT,
  `Model` varchar(255) DEFAULT NULL,
  `Cihaz Seri No` varchar(50) NOT NULL,
  `Anakart No` varchar(50) DEFAULT NULL,
  `UID No` varchar(12) DEFAULT NULL,
  `Modem Kartı` varchar(50) DEFAULT NULL,
  `Lcd Kartı` varchar(50) DEFAULT NULL,
  `Şarj Kartı` varchar(50) DEFAULT NULL,
  `Durumu` varchar(255) DEFAULT NULL,
  `Modem Tipi` varchar(50) DEFAULT NULL,
  `Müşteri Adı` varchar(255) DEFAULT NULL,
  `Modem Seri Num 1` varchar(255) DEFAULT NULL,
  `Modem Seri Num 2` varchar(255) DEFAULT NULL,
  `Modem Seri Num 3` varchar(255) DEFAULT NULL,
  `Modem Seri Num 4` varchar(255) DEFAULT NULL,
  `Modem Seri Num 5` varchar(255) DEFAULT NULL,
  `Modem Seri Num 6` varchar(255) DEFAULT NULL,
  `Uretim Tarihi` varchar(10) DEFAULT NULL,
  `Test Durumu` varchar(255) DEFAULT NULL,
  `Notlar` text,
  PRIMARY KEY (`Sıra`),
  UNIQUE KEY `Sıra` (`Sıra`),
  UNIQUE KEY `Cihaz Seri No` (`Cihaz Seri No`),
  UNIQUE KEY `Sıra_2` (`Sıra`)
) ENGINE=InnoDB AUTO_INCREMENT=196 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cihazkimlikmobiot`
--

DROP TABLE IF EXISTS `cihazkimlikmobiot`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cihazkimlikmobiot` (
  `Sıra` int(11) NOT NULL AUTO_INCREMENT,
  `Model` varchar(55) NOT NULL,
  `Cihaz Seri No` varchar(55) NOT NULL,
  `Anakart No` varchar(55) NOT NULL,
  `UID No` varchar(55) NOT NULL,
  `Test Durumu` varchar(55) NOT NULL,
  `Müşteri` varchar(55) NOT NULL,
  `Durum` varchar(55) NOT NULL,
  `Üretim Tarihi` varchar(55) NOT NULL,
  `Modem Tipi` varchar(55) NOT NULL,
  `IMEI 1` varchar(55) NOT NULL,
  `IMEI 2` varchar(55) NOT NULL,
  `IMEI 3` varchar(55) NOT NULL,
  `Notlar` text NOT NULL,
  PRIMARY KEY (`Sıra`),
  UNIQUE KEY `Cihaz Seri No` (`Cihaz Seri No`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cihazkimlikserver`
--

DROP TABLE IF EXISTS `cihazkimlikserver`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cihazkimlikserver` (
  `Sıra` int(11) NOT NULL AUTO_INCREMENT,
  `Model` varchar(55) NOT NULL,
  `Cihaz Seri No` varchar(55) NOT NULL,
  `Anakart No` varchar(55) NOT NULL,
  `UID No` varchar(55) NOT NULL,
  `İşlemci` varchar(55) NOT NULL,
  `Ram` varchar(55) NOT NULL,
  `Decklink` varchar(55) NOT NULL,
  `Kasa Tipi` varchar(55) NOT NULL,
  `Test Durumu` varchar(55) NOT NULL,
  `Müşteri` varchar(55) NOT NULL,
  `Durum` varchar(55) NOT NULL,
  `Üretim Tarihi` varchar(55) NOT NULL,
  `HDD` varchar(55) NOT NULL,
  `Notlar` text NOT NULL,
  PRIMARY KEY (`Sıra`),
  UNIQUE KEY `Cihaz Seri No` (`Cihaz Seri No`),
  KEY `Müşteri` (`Müşteri`),
  CONSTRAINT `cihazkimlikserver_ibfk_1` FOREIGN KEY (`Müşteri`) REFERENCES `müsteri` (`İsim`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `kullanıcılar`
--

DROP TABLE IF EXISTS `kullanıcılar`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kullanıcılar` (
  `name` varchar(55) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `loglar`
--

DROP TABLE IF EXISTS `loglar`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `loglar` (
  `Cihaz Seri No` varchar(50) NOT NULL,
  `Tarih` varchar(55) NOT NULL,
  `Eski Deger` varchar(255) NOT NULL,
  `Yeni Deger` varchar(55) NOT NULL,
  `Değişen` varchar(55) NOT NULL,
  KEY `Cihaz Seri No` (`Cihaz Seri No`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `müsteri`
--

DROP TABLE IF EXISTS `müsteri`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `müsteri` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `İsim` varchar(55) NOT NULL,
  `Adres` varchar(255) DEFAULT NULL,
  `Cihaz Seri No` varchar(750) NOT NULL,
  PRIMARY KEY (`İsim`),
  UNIQUE KEY `Id` (`Id`),
  UNIQUE KEY `Cihaz Seri No` (`Cihaz Seri No`)
) ENGINE=InnoDB AUTO_INCREMENT=335 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `model`
--

DROP TABLE IF EXISTS `model`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `model` (
  `name` varchar(55) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `modemtipi`
--

DROP TABLE IF EXISTS `modemtipi`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `modemtipi` (
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `simkart`
--

DROP TABLE IF EXISTS `simkart`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `simkart` (
  `Num` varchar(55) NOT NULL,
  `Kart Seri No` varchar(55) NOT NULL,
  `Kota` varchar(55) NOT NULL,
  `Taahhüt` varchar(55) NOT NULL,
  `Müşteri` varchar(55) NOT NULL,
  `Tarih` varchar(55) NOT NULL,
  PRIMARY KEY (`Kart Seri No`),
  UNIQUE KEY `Kart Seri No` (`Kart Seri No`),
  KEY `Müşteri` (`Müşteri`),
  CONSTRAINT `simkart_ibfk_1` FOREIGN KEY (`Müşteri`) REFERENCES `müsteri` (`İsim`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `teknikservis`
--

DROP TABLE IF EXISTS `teknikservis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teknikservis` (
  `Sıra` int(11) NOT NULL AUTO_INCREMENT,
  `Cihaz Seri No` varchar(50) NOT NULL,
  `Tarih` varchar(50) NOT NULL,
  `Olay` varchar(25) NOT NULL,
  `Yapılan İşlem` mediumtext NOT NULL,
  `Cihazla Gelen Malzemeler` text NOT NULL,
  `Degisen Parcalar` varchar(255) NOT NULL,
  `Test Süresi` varchar(255) NOT NULL,
  `Notlar` text NOT NULL,
  PRIMARY KEY (`Sıra`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-08-09 15:41:58
