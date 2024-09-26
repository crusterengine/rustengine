# Before Running Benchmarks

- Shut down as many external programs as possible, in particular:
  - Web browsers
  - Skype
  - Microsoft Office / OpenOffice
  - Mail clients
  - Virus checkers
  - iTunes
  - Virtual machines (e.g., Virtual PC, Parallels, VMware)
  - Web servers and database servers running on the same machine
  - *(From Peter’s benchmarking paper)*

- Run the benchmarking tools from the terminal:  
  **“Never measure performance from inside an integrated development environment (IDE) such as Eclipse or Visual Studio; use the command line.”**  
  *(From Peter’s benchmarking paper)*

- **“Turn off power-saving schemes in your operating system and BIOS, to prevent them from reducing CPU speed in the middle of the benchmark run.”**  
  *(From Peter’s benchmarking paper)*

- Have full power and make sure to have the charger plugged in.

- Ensure that the screen does not go into sleep mode (by adjusting the settings).

- When running Valgrind, compile the code with the `-g` flag (for debugging). For `gtime`, do not compile in debug mode. Rust code compiled with `cargo build --release` works for both tools.

---

# Running the Benchmarks

- Run the benchmark **xx** times with the same number of iterations, and take the average as the ‘final’ result.

---

# After Running the Benchmarks

1. Extract the CSV file into Excel.
2. Change the data so it is in the correct columns and rows.
3. Take the average of the results for each size.
4. Create a scatter plot (XY plot) for memory usage and execution time.

