package main

import "C"
import "fmt"

//export go_foo
func go_foo() {
	fmt.Println("hello from Go")
}
