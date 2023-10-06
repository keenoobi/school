package main

import (
	"text/scanner"
	"os"
	"fmt"
)
func main() {
	var s scanner.Scanner
	s.Init(os.Stdin)
	s.Mode = scanner.GoTokens
	for token := s.Scan(); token != scanner.EOF; token = s.Scan() {
		fmt.Println(s.TokenText())
	}
}