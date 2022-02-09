-- ---------------------
-- For require
-- ---------------------
package.path = "plugins/lib/?.lua;"..package.path


-- ---------------------
-- For Compatibility
-- ---------------------
file = File
__BasePath__ = file.getCurrentDirectory();