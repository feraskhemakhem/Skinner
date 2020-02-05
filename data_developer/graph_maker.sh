cd ../build
make -j4
./A6 5 1000 100 10 2 0 5
cd ../data_developer
python3 graph_maker.py
cd ../data 
rm temp.txt