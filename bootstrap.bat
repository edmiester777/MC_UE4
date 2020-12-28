@echo off
setlocal
cd third-party\mcp-reborn
.\gradlew.bat --gradle-user-home="gradle_install" setup build
endlocal