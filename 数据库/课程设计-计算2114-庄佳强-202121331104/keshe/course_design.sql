-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: localhost    Database: course_design
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `college`
--

DROP TABLE IF EXISTS `college`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `college` (
  `college_id` int NOT NULL AUTO_INCREMENT,
  `college_name` varchar(50) NOT NULL,
  `address` varchar(100) NOT NULL,
  PRIMARY KEY (`college_id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `college`
--

LOCK TABLES `college` WRITE;
/*!40000 ALTER TABLE `college` DISABLE KEYS */;
INSERT INTO `college` VALUES (1,'计算机工程学院','厦门'),(2,'海洋学院','厦门'),(3,'北京信息学院','北京'),(4,'厦门理工大学','厦门'),(14,'厦门大学学院','厦门'),(15,'厦门小学','泉州');
/*!40000 ALTER TABLE `college` ENABLE KEYS */;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `insert_record_operation_log_trigger` AFTER INSERT ON `college` FOR EACH ROW begin
        insert into operation_record
            (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
            value (null,'college','insert',NEW.college_id,NOW(),user());
    end */;;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `update_record_operation_log_trigger` AFTER UPDATE ON `college` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'college','update',NEW.college_id,NOW(),user());
end */;;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `delete_record_operation_log_trigger` AFTER DELETE ON `college` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'college','delete',OLD.college_id,NOW(),user());
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `leader`
--

DROP TABLE IF EXISTS `leader`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `leader` (
  `leader_id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(20) NOT NULL,
  `age` int NOT NULL,
  `job` varchar(20) NOT NULL,
  `college_id` int NOT NULL,
  PRIMARY KEY (`leader_id`),
  KEY `college_id` (`college_id`),
  CONSTRAINT `leader_ibfk_1` FOREIGN KEY (`college_id`) REFERENCES `college` (`college_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `leader`
--

LOCK TABLES `leader` WRITE;
/*!40000 ALTER TABLE `leader` DISABLE KEYS */;
INSERT INTO `leader` VALUES (1,'老八',20,'学生',2),(2,'老六',20,'学生',1),(3,'小米',20,'学生',3),(4,'老爹',30,'CEO',1);
/*!40000 ALTER TABLE `leader` ENABLE KEYS */;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `insert_leader_record_operation_log_trigger` AFTER INSERT ON `leader` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'leader','insert',NEW.leader_id,NOW(),user());
end */;;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `update_leader_record_operation_log_trigger` AFTER UPDATE ON `leader` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'leader','update',NEW.leader_id,NOW(),user());
end */;;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `delete_leader_record_operation_log_trigger` AFTER DELETE ON `leader` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'leader','delete',OLD.leader_id,NOW(),user());
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `operation_record`
--

DROP TABLE IF EXISTS `operation_record`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `operation_record` (
  `Operation_record_id` int NOT NULL AUTO_INCREMENT,
  `record_table` varchar(20) NOT NULL,
  `record_operation` varchar(20) NOT NULL,
  `record_id` int NOT NULL,
  `record_date` date NOT NULL,
  `operator` varchar(20) NOT NULL,
  PRIMARY KEY (`Operation_record_id`)
) ENGINE=InnoDB AUTO_INCREMENT=116 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `operation_record`
--

LOCK TABLES `operation_record` WRITE;
/*!40000 ALTER TABLE `operation_record` DISABLE KEYS */;
INSERT INTO `operation_record` VALUES (1,'college','update',1,'2023-06-11','root@localhost'),(2,'college','insert',2,'2023-06-11','root@localhost'),(3,'college','insert',3,'2023-06-11','root@localhost'),(4,'leader','insert',1,'2023-06-11','root@localhost'),(5,'leader','insert',2,'2023-06-11','root@localhost'),(6,'leader','insert',3,'2023-06-11','root@localhost'),(10,'project','insert',1,'2023-06-11','root@localhost'),(11,'project','insert',2,'2023-06-11','root@localhost'),(12,'project','insert',3,'2023-06-11','root@localhost'),(13,'college','insert',4,'2023-06-11','root@localhost'),(14,'college','update',4,'2023-06-11','root@localhost'),(15,'college','update',2,'2023-06-11','root@localhost'),(16,'college','update',1,'2023-06-11','root@localhost'),(17,'college','update',3,'2023-06-11','root@localhost'),(18,'leader','insert',4,'2023-06-12','root@localhost'),(19,'leader','insert',5,'2023-06-12','root@localhost'),(20,'college','update',1,'2023-06-12','root@localhost'),(21,'leader','delete',5,'2023-06-12','root@localhost'),(22,'leader','update',4,'2023-06-12','root@localhost'),(23,'project','update',1,'2023-06-12','root@localhost'),(24,'project','update',1,'2023-06-12','root@localhost'),(25,'project','update',1,'2023-06-12','root@localhost'),(26,'project','update',1,'2023-06-12','root@localhost'),(27,'project','update',1,'2023-06-12','root@localhost'),(28,'college','insert',5,'2023-06-12','root@localhost'),(29,'college','insert',6,'2023-06-12','root@localhost'),(30,'college','insert',7,'2023-06-12','root@localhost'),(31,'college','insert',8,'2023-06-12','root@localhost'),(32,'college','insert',9,'2023-06-12','root@localhost'),(33,'college','insert',10,'2023-06-12','root@localhost'),(34,'college','insert',11,'2023-06-12','root@localhost'),(35,'college','insert',12,'2023-06-12','root@localhost'),(36,'college','delete',5,'2023-06-12','root@localhost'),(37,'college','delete',7,'2023-06-12','root@localhost'),(38,'college','delete',11,'2023-06-12','root@localhost'),(39,'college','delete',9,'2023-06-12','root@localhost'),(40,'college','delete',8,'2023-06-12','root@localhost'),(41,'college','delete',6,'2023-06-12','root@localhost'),(42,'college','delete',12,'2023-06-12','root@localhost'),(43,'college','delete',10,'2023-06-12','root@localhost'),(44,'college','insert',13,'2023-06-12','root@localhost'),(45,'college','delete',13,'2023-06-12','root@localhost'),(46,'college','update',4,'2023-06-12','root@localhost'),(47,'leader','insert',6,'2023-06-13','root@localhost'),(48,'leader','insert',7,'2023-06-13','root@localhost'),(49,'leader','delete',7,'2023-06-13','root@localhost'),(50,'leader','insert',8,'2023-06-13','root@localhost'),(51,'leader','delete',6,'2023-06-13','root@localhost'),(52,'leader','update',8,'2023-06-13','root@localhost'),(53,'leader','delete',8,'2023-06-13','root@localhost'),(54,'project','insert',4,'2023-06-13','root@localhost'),(57,'project','delete',4,'2023-06-13','root@localhost'),(58,'project','insert',5,'2023-06-13','root@localhost'),(61,'project','delete',5,'2023-06-13','root@localhost'),(62,'project','insert',6,'2023-06-13','root@localhost'),(64,'project','update',6,'2023-06-13','root@localhost'),(67,'college','delete',4,'2023-06-13','root@localhost'),(68,'college','insert',4,'2023-06-13','root@localhost'),(69,'project','insert',7,'2023-06-13','root@localhost'),(71,'project','update',1,'2023-06-13','root@localhost'),(72,'project','update',1,'2023-06-13','root@localhost'),(73,'project','update',1,'2023-06-13','root@localhost'),(74,'project','update',1,'2023-06-13','root@localhost'),(75,'project','update',1,'2023-06-13','root@localhost'),(77,'project','insert',1,'2023-06-13','root@localhost'),(79,'project','insert',2,'2023-06-13','root@localhost'),(81,'project','insert',3,'2023-06-13','root@localhost'),(83,'project','insert',4,'2023-06-13','root@localhost'),(85,'project','insert',5,'2023-06-13','root@localhost'),(86,'project','update',1,'2023-06-13','root@localhost'),(87,'project','update',1,'2023-06-13','root@localhost'),(88,'project','update',1,'2023-06-13','root@localhost'),(89,'project','update',1,'2023-06-13','root@localhost'),(90,'project','update',3,'2023-06-13','root@localhost'),(91,'project','update',2,'2023-06-13','root@localhost'),(92,'project','update',5,'2023-06-13','root@localhost'),(93,'project','update',4,'2023-06-13','root@localhost'),(99,'project','delete',5,'2023-06-13','root@localhost'),(100,'project','delete',2,'2023-06-13','root@localhost'),(101,'project','delete',1,'2023-06-13','root@localhost'),(102,'project','delete',3,'2023-06-13','root@localhost'),(103,'project','delete',4,'2023-06-13','root@localhost'),(106,'project','insert',1,'2023-06-13','root@localhost'),(107,'project','insert',2,'2023-06-13','root@localhost'),(108,'project','insert',3,'2023-06-13','root@localhost'),(109,'project','insert',4,'2023-06-13','root@localhost'),(110,'project','insert',5,'2023-06-13','root@localhost'),(111,'college','insert',14,'2023-06-13','root@localhost'),(112,'college','insert',15,'2023-06-14','root@localhost'),(113,'college','insert',16,'2023-06-15','root@localhost'),(114,'college','update',16,'2023-06-15','root@localhost'),(115,'college','delete',16,'2023-06-15','root@localhost');
/*!40000 ALTER TABLE `operation_record` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `project`
--

DROP TABLE IF EXISTS `project`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `project` (
  `project_id` int NOT NULL AUTO_INCREMENT,
  `project_name` varchar(50) NOT NULL,
  `project_level` varchar(20) NOT NULL,
  `leader_id` int NOT NULL,
  `start_date` date NOT NULL,
  `budget` decimal(10,2) NOT NULL,
  `data` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`project_id`),
  KEY `leader_id` (`leader_id`),
  CONSTRAINT `project_ibfk_1` FOREIGN KEY (`leader_id`) REFERENCES `leader` (`leader_id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `project`
--

LOCK TABLES `project` WRITE;
/*!40000 ALTER TABLE `project` DISABLE KEYS */;
INSERT INTO `project` VALUES (1,'数据库课设','个人',1,'2023-06-11',0.00,'C://img1.jpg'),(2,'操作系统课设','个人',2,'2023-06-11',0.00,'C:/Uploads/img1.jpg'),(3,'网络课设','个人',3,'2023-06-11',0.00,'C:/Uploads/img1.jpg'),(4,'demo','校级',1,'2023-06-11',10.00,'C:/Uploads/img1.jpg'),(5,'一号工程','校级',3,'2023-06-11',100000.00,'C:/Uploads/img1.jpg');
/*!40000 ALTER TABLE `project` ENABLE KEYS */;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `insert_project_record_operation_log_trigger` AFTER INSERT ON `project` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'project','insert',NEW.project_id,NOW(),user());
end */;;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `project_insert_trigger` AFTER INSERT ON `project` FOR EACH ROW begin
    insert into project_college
    (project_id, college_id)
        value (NEW.project_id,
               (select college_id from leader where NEW.leader_id=Leader.leader_id)
               );

end */;;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `update_project_record_operation_log_trigger` AFTER UPDATE ON `project` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'project','update',NEW.project_id,NOW(),user());
end */;;
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `delete_project_record_operation_log_trigger` AFTER DELETE ON `project` FOR EACH ROW begin
    insert into operation_record
    (Operation_record_id,record_table,record_operation,record_id,record_date,operator)
        value (null,'project','delete',OLD.project_id,NOW(),user());
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `project_college`
--

DROP TABLE IF EXISTS `project_college`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `project_college` (
  `project_id` int NOT NULL,
  `college_id` int NOT NULL,
  PRIMARY KEY (`project_id`,`college_id`),
  KEY `college_id` (`college_id`),
  CONSTRAINT `project_college_ibfk_1` FOREIGN KEY (`project_id`) REFERENCES `project` (`project_id`),
  CONSTRAINT `project_college_ibfk_2` FOREIGN KEY (`college_id`) REFERENCES `college` (`college_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `project_college`
--

LOCK TABLES `project_college` WRITE;
/*!40000 ALTER TABLE `project_college` DISABLE KEYS */;
INSERT INTO `project_college` VALUES (2,1),(1,2),(4,2),(3,3),(5,3);
/*!40000 ALTER TABLE `project_college` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `user` varchar(20) NOT NULL,
  `password` varchar(200) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES ('老六','e10adc3949ba59abbe56e057f20f883e'),('老八','e10adc3949ba59abbe56e057f20f883e'),('老七','fcea920f7412b5da7be0cf42b8c93759'),('1','202cb962ac59075b964b07152d234b70'),('U001','202cb962ac59075b964b07152d234b70');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-06-15 11:33:46
