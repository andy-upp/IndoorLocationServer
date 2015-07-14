/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `WifiQuery_wmap`;

DROP TABLE IF EXISTS `WifiQuery`;

DROP TABLE IF EXISTS `WifiRaw`;

DROP TABLE IF EXISTS `WifiSample`;

DROP TABLE IF EXISTS `WifiData_wmap`;

DROP TABLE IF EXISTS `WifiData`;

CREATE TABLE `WifiData` (
  `id` BIGINT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `pos` TEXT NOT NULL)
 ENGINE=InnoDB;

CREATE TABLE `WifiData_wmap` (
  `object_id` BIGINT UNSIGNED NOT NULL,
  `key` TEXT NOT NULL,
  `value` DOUBLE NOT NULL,
  CONSTRAINT `WifiData_wmap_object_id_fk`
    FOREIGN KEY (`object_id`)
    REFERENCES `WifiData` (`id`)
    ON DELETE CASCADE)
 ENGINE=InnoDB;

CREATE INDEX `object_id_i`
  ON `WifiData_wmap` (`object_id`);

CREATE TABLE `WifiSample` (
  `raw_id` BIGINT UNSIGNED NOT NULL PRIMARY KEY)
 ENGINE=InnoDB;

CREATE TABLE `WifiRaw` (
  `id` BIGINT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `identification` TEXT NOT NULL,
  `name` TEXT NOT NULL,
  `device` TEXT NOT NULL,
  `nowtime` TEXT NOT NULL,
  `intensity` INT NOT NULL,
  `pos` TEXT NOT NULL)
 ENGINE=InnoDB;

CREATE TABLE `WifiQuery` (
  `id` BIGINT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `pos` TEXT NOT NULL)
 ENGINE=InnoDB;

CREATE TABLE `WifiQuery_wmap` (
  `object_id` BIGINT UNSIGNED NOT NULL,
  `key` TEXT NOT NULL,
  `value` DOUBLE NOT NULL,
  CONSTRAINT `WifiQuery_wmap_object_id_fk`
    FOREIGN KEY (`object_id`)
    REFERENCES `WifiQuery` (`id`)
    ON DELETE CASCADE)
 ENGINE=InnoDB;

CREATE INDEX `object_id_i`
  ON `WifiQuery_wmap` (`object_id`);

