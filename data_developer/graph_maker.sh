cd ../build
make -j4
./A6 3 1000 100 10 2 0 5 # with 3 bones
cd ../data_developer
python3 graph_maker.py linear_interpolation.png
cd ../data 
rm temp.txt