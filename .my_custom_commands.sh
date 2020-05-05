function compileAndExecute() {
  clang -std=c11 -Wall  $1 -o $2
  ./$2
}
