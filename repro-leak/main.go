package main

// extern void bar(void);
import "C"

func main() {
	for true {
		C.bar()
	}
}
