ALTER TABLE character_db_version CHANGE COLUMN required_s2388_01_characters_fix_skills_overflow required_s2389_00_characters_cooldown bit;

ALTER TABLE character_spell_cooldown CHANGE COLUMN `LowGuid` `guid` int(11);
