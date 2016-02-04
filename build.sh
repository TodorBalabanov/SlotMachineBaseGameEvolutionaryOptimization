clear
astyle "*.cpp" --indent=force-tab --style=java / -A2 --recursive
astyle "*.c" --indent=force-tab --style=java / -A2 --recursive
astyle "*.h" --indent=force-tab --style=java / -A2 --recursive
find . -name "*.orig" -type f -delete
rm BaseRTP.exe
mpicxx BaseRTP.cpp -o BaseRTP.exe
-nohup nice mpirun -np 8 ./BaseRTP.exe $1
