package main

import "C"
import "fmt"

//export foo
func foo() {
	fmt.Println("hello from Go")
}
