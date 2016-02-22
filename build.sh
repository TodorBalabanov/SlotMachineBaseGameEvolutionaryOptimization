clear
astyle "*.cpp" --indent=force-tab --style=java / -A2 --recursive
astyle "*.c" --indent=force-tab --style=java / -A2 --recursive
astyle "*.h" --indent=force-tab --style=java / -A2 --recursive
find . -name "*.orig" -type f -delete
rm BaseRTP.exe
mpicxx BaseRTP.cpp -o BaseRTP.exe
mpirun -np 8 ./BaseRTP.exe >results_$(date +"%Y_%m_%d_%H_%M_%S").txt
