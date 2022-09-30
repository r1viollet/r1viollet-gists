package main

import (
    "fmt"
	"sync"
)

// extern void bar(void);
import "C"

func infinite_thread_create(idx int) {
	fmt.Println("Goroutine --", idx)
	for {
		C.bar()
	}
}

func main() {
	var wg sync.WaitGroup

	for i := 0; i < 10; i++ {
		wg.Add(1)
		// 10 goroutines
		go func() {
            defer wg.Done()
            infinite_thread_create(i)
        }()
	}
	wg.Wait()
}
