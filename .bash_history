ls
git clone https://github-dev.cs.illinois.edu/cs240-sp21/kjzhou2.git
git fetch release
ls
cd kjzhou2
git fetch release
git remote add release https://github-dev.cs.illinois.edu/cs240-sp21/_release.git
git config user.name "Kevin Zhou"
git config user.email "kjzhou2@illinois.edu"
git fetch release
git merge release/mp1 -m "Merging initial files"
ls
cd mp1
make
./mp1
git push
vim
cd..
quit
exit
