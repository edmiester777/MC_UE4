@echo off
setlocal
cd third-party\mcp-reborn
.\gradlew.bat setup
.\gradlew.bat build
endlocal