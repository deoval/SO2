cd build
mkdir test
cd test
../touch a b c d e
ls -l
echo "Escreva conteudo de A."
../cat > a
echo "O conteudo foi:"
../cat a
mkdir test2
../cp a b c d e test2
cd test2
echo "O conteudo de test2"
ls -l
cd ../..
./rm -rf test
ls -l
# echo $PATH
