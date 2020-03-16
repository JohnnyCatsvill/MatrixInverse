Debug\MatrixInverse.exe input.txt
echo ERROR=%ERRORLEVEL% ? 0

Debug\MatrixInverse.exe input2.txt
echo ERROR=%ERRORLEVEL% ? 2

Debug\MatrixInverse.exe
echo ERROR=%ERRORLEVEL% ? 3

Debug\MatrixInverse.exe noinput.txt
echo ERROR=%ERRORLEVEL% ? 1
pause