ALTER TABLE db_version CHANGE COLUMN required_s1272_11565_01_mangos_mangos_string required_s1308_xxxxx_01_mangos_instance_template bit;

UPDATE instance_template
SET reset_delay = 0;
