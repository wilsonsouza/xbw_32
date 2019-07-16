
USE Group_A_a_Z_PagesByGroup_25_NumbersByGroup_25_NumbersByPage_15_
GO

IF OBJECT_ID ('dbo.Controller') IS NOT NULL
	DROP TABLE dbo.Controller
GO

IF OBJECT_ID ('dbo.Information') IS NOT NULL
	DROP TABLE dbo.Information
GO

IF OBJECT_ID ('dbo.Numbers') IS NOT NULL
	DROP TABLE dbo.Numbers
GO

IF OBJECT_ID ('dbo.Resources') IS NOT NULL
	DROP TABLE dbo.Resources
GO

CREATE TABLE dbo.Controller
	(
	groupname   VARCHAR (10) COLLATE Latin1_General_CI_AS NULL,
	iscompleted INT DEFAULT ((0)) NULL,
	pagename    INT DEFAULT ((0)) NULL
	)
GO

CREATE TABLE dbo.Information
	(
	groupsid          VARCHAR (1) COLLATE Latin1_General_CI_AS NULL,
	groupname         VARCHAR (10) COLLATE Latin1_General_CI_AS NULL,
	pagesbygroup      INT DEFAULT ((0)) NULL,
	numbersbygroup    INT DEFAULT ((0)) NULL,
	numbersbypage     INT DEFAULT ((0)) NULL,
	numbers           INT DEFAULT ((0)) NULL,
	iscreateallgroups BIT DEFAULT ((0)) NULL,
	isallowedzero     BIT DEFAULT ((0)) NULL,
	iscompleted       BIT DEFAULT ((0)) NULL,
	created           DATETIME DEFAULT (getdate()) NULL,
	lastupdated       DATETIME DEFAULT (getdate()) NULL,
	byusername        VARCHAR (255) COLLATE Latin1_General_CI_AS NULL,
	versionid         FLOAT NULL,
	lastaccess        DATETIME NULL,
	comments          VARCHAR (255) COLLATE Latin1_General_CI_AS NULL
	)
GO

CREATE TABLE dbo.Numbers
	(
	groupname   VARCHAR (10) COLLATE Latin1_General_CI_AS NULL,
	pagename    INT DEFAULT ((0)) NULL,
	numbers     INT DEFAULT ((0)) NULL,
	iscompleted BIT DEFAULT ((0)) NULL,
	useds       INT DEFAULT ((0)) NULL,
	availables  INT DEFAULT ((0)) NULL
	)
GO

CREATE TABLE dbo.Resources
	(
	groupname  VARCHAR (10) COLLATE Latin1_General_CI_AS NULL,
	numbers    INT DEFAULT ((0)) NULL,
	useds      INT DEFAULT ((0)) NULL,
	availables INT DEFAULT ((0)) NULL
	)
GO

