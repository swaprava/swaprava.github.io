Download the package from Gurobi site. Extract and keep at some place -- e.g., in Downloads.

collect the academic license: grbgetkey <key blah blah>

update the .bashrc file with the lines:

export GUROBI_HOME="/home/swaprava/Downloads/gurobi8.1.0_linux64/gurobi810/linux64" -- actually wherever your binaries are extracted.
export PATH="${PATH}:${GUROBI_HOME}/bin" 
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${GUROBI_HOME}/lib"

go to the bin/ folder in the extracted binary, you'll find a grbgetkey executable there. run that with the academic license key. make sure your computer has an active internet connection. once it's successfully done, it will ask where to save the gurobi.lic file. E.g., save it in the same Downloads/ folder. Then add the following line to the .bashrc:

export GRB_LICENSE_FILE="/home/swaprava/Downloads/gurobi.lic"

for the bash to take effect restart the terminal -- close and open again.

go to the folder: /home/swaprava/Downloads/gurobi8.1.0_linux64/gurobi810/linux64/.

run
sudo python setup.py build
sudo python setup.py install

You're all set to rock. Run your python code with the gurobipy imported. Things should work as expected.
