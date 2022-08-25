-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Anamakine: 127.0.0.1
-- Üretim Zamanı: 27 Tem 2022, 13:30:45
-- Sunucu sürümü: 10.4.24-MariaDB
-- PHP Sürümü: 8.0.19

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Veritabanı: `modeo`
--

-- --------------------------------------------------------

--
-- Tablo için tablo yapısı `cihazkimlik`
--

CREATE TABLE `cihazkimlik` (
  `Sıra` int(11) NOT NULL,
  `Model` varchar(255) DEFAULT NULL,
  `Cihaz Seri No` varchar(50) NOT NULL,
  `Anakart No` varchar(50) NOT NULL,
  `UID No` varchar(12) NOT NULL,
  `Modem Kartı` varchar(50) NOT NULL,
  `Lcd Kartı` varchar(50) NOT NULL,
  `Şarj Kartı` varchar(50) NOT NULL,
  `Durumu` varchar(255) DEFAULT NULL,
  `Müşteri Adı` varchar(255) NOT NULL,
  `Modem Seri Num 1` varchar(255) DEFAULT NULL,
  `Modem Seri Num 2` varchar(255) DEFAULT NULL,
  `Modem Seri Num 3` varchar(255) DEFAULT NULL,
  `Modem Seri Num 4` varchar(255) DEFAULT NULL,
  `Modem Seri Num 5` varchar(255) DEFAULT NULL,
  `Modem Seri Num 6` varchar(255) DEFAULT NULL,
  `Uretim Tarihi` varchar(10) NOT NULL,
  `Test Durumu` varchar(255) DEFAULT NULL,
  `Notlar` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Tablo için tablo yapısı `loglar`
--

CREATE TABLE `loglar` (
  `Cihaz Seri No` varchar(50) NOT NULL,
  `Tarih` varchar(55) NOT NULL,
  `Eski Deger` varchar(255) NOT NULL,
  `Yeni Deger` varchar(55) NOT NULL,
  `Değişen` varchar(55) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Tablo için tablo yapısı `müsteri`
--

CREATE TABLE `müsteri` (
  `Id` int(11) NOT NULL,
  `İsim` varchar(55) NOT NULL,
  `Adres` varchar(255) NOT NULL,
  `Cihaz Seri No` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Tablo için tablo yapısı `teknikservis`
--

CREATE TABLE `teknikservis` (
  `Sıra` int(11) NOT NULL,
  `Cihaz Seri No` varchar(50) NOT NULL,
  `Tarih` varchar(50) NOT NULL,
  `Saat` varchar(55) NOT NULL,
  `Olay` varchar(25) NOT NULL,
  `Yapılan İşlem` varchar(255) NOT NULL,
  `Cihazla Gelen Malzemeler` text NOT NULL,
  `Degisen Parcalar` varchar(255) NOT NULL,
  `Test Süresi` varchar(255) NOT NULL,
  `Notlar` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dökümü yapılmış tablolar için indeksler
--

--
-- Tablo için indeksler `cihazkimlik`
--
ALTER TABLE `cihazkimlik`
  ADD PRIMARY KEY (`Sıra`),
  ADD UNIQUE KEY `Sıra` (`Sıra`),
  ADD UNIQUE KEY `Cihaz Seri No` (`Cihaz Seri No`),
  ADD UNIQUE KEY `Sıra_2` (`Sıra`);

--
-- Tablo için indeksler `loglar`
--
ALTER TABLE `loglar`
  ADD KEY `Cihaz Seri No` (`Cihaz Seri No`);

--
-- Tablo için indeksler `müsteri`
--
ALTER TABLE `müsteri`
  ADD PRIMARY KEY (`Cihaz Seri No`),
  ADD UNIQUE KEY `Id` (`Id`);

--
-- Tablo için indeksler `teknikservis`
--
ALTER TABLE `teknikservis`
  ADD PRIMARY KEY (`Sıra`);

--
-- Dökümü yapılmış tablolar için AUTO_INCREMENT değeri
--

--
-- Tablo için AUTO_INCREMENT değeri `cihazkimlik`
--
ALTER TABLE `cihazkimlik`
  MODIFY `Sıra` int(11) NOT NULL AUTO_INCREMENT;

--
-- Tablo için AUTO_INCREMENT değeri `müsteri`
--
ALTER TABLE `müsteri`
  MODIFY `Id` int(11) NOT NULL AUTO_INCREMENT;

--
-- Tablo için AUTO_INCREMENT değeri `teknikservis`
--
ALTER TABLE `teknikservis`
  MODIFY `Sıra` int(11) NOT NULL AUTO_INCREMENT;

--
-- Dökümü yapılmış tablolar için kısıtlamalar
--

--
-- Tablo kısıtlamaları `loglar`
--
ALTER TABLE `loglar`
  ADD CONSTRAINT `loglar_ibfk_1` FOREIGN KEY (`Cihaz Seri No`) REFERENCES `cihazkimlik` (`Cihaz Seri No`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
