# 8085 Emulator Instructions

This project aims to emulate the 8085 microprocessor and implement all its instructions with appropriate flag handling. Below is a checklist of all 8085 instructions grouped by categories.

## Data Transfer Instructions

| Instruction | Description                             | Status     |
|-------------|-----------------------------------------|------------|
| MOV         | Move data between registers.           | ✅ Done    |
| MVI         | Move immediate data.                   | ✅ Done    |
| LDA         | Load accumulator directly.             | ✅ Done    |
| STA         | Store accumulator directly.            | ✅ Done    |
| LDAX        | Load accumulator indirectly.           | ✅ Done    |
| STAX        | Store accumulator indirectly.          | ✅ Done    |
| LHLD        | Load H-L pair directly.                | ✅ Done    |
| SHLD        | Store H-L pair directly.               | ✅ Done    |
| XCHG        | Exchange H-L with D-E.                 | ✅ Done    |
| PUSH        | Push register pair onto the stack.     | ✅ Done    |
| POP         | Pop register pair from the stack.      | 🔲 Pending |
| OUT         | Output to port.                        | ✅ Done    |
| IN          | Input from port.                       | 🔲 Pending |

## Arithmetic Instructions

| Instruction | Description                                     | Status     |
|-------------|-------------------------------------------------|------------|
| ADD         | Add register to accumulator.                   | 🔲 Pending |
| ADC         | Add register to accumulator with carry.        | 🔲 Pending |
| SUB         | Subtract register from accumulator.            | 🔲 Pending |
| SBB         | Subtract register with borrow.                 | 🔲 Pending |
| INR         | Increment register.                            | 🔲 Pending |
| DCR         | Decrement register.                            | 🔲 Pending |
| CMP         | Compare register with accumulator.             | ✅ Done    |
| CPI         | Compare immediate with accumulator.            | 🔲 Pending |

## Logical Instructions

| Instruction | Description                                     | Status     |
|-------------|-------------------------------------------------|------------|
| ANA         | AND register with accumulator.                 | 🔲 Pending |
| ANI         | AND immediate with accumulator.                | 🔲 Pending |
| ORA         | OR register with accumulator.                  | 🔲 Pending |
| ORI         | OR immediate with accumulator.                 | 🔲 Pending |
| XRA         | XOR register with accumulator.                 | 🔲 Pending |
| XRI         | XOR immediate with accumulator.                | 🔲 Pending |
| CMA         | Complement accumulator.                        | 🔲 Pending |
| CMC         | Complement carry flag.                         | 🔲 Pending |
| STC         | Set carry flag.                                | 🔲 Pending |

## Branching Instructions

| Instruction | Description                                     | Status     |
|-------------|-------------------------------------------------|------------|
| JMP         | Jump unconditionally.                          | 🔲 Pending |
| JC          | Jump if carry is set.                          | 🔲 Pending |
| JNC         | Jump if carry is not set.                      | 🔲 Pending |
| JZ          | Jump if zero.                                  | 🔲 Pending |
| JNZ         | Jump if not zero.                              | 🔲 Pending |
| CALL        | Call subroutine.                               | 🔲 Pending |
| RET         | Return from subroutine.                        | 🔲 Pending |
| RST         | Restart (vector interrupt).                    | 🔲 Pending |

## Stack & Machine Control Instructions

| Instruction | Description                                     | Status     |
|-------------|-------------------------------------------------|------------|
| PUSH        | Push register pair onto the stack.             | ✅ Done    |
| POP         | Pop register pair from the stack.              | 🔲 Pending |
| HLT         | Halt the program.                              | 🔲 Pending |
| NOP         | No operation.                                  | 🔲 Pending |
| DI          | Disable interrupts.                            | 🔲 Pending |
| EI          | Enable interrupts.                             | 🔲 Pending |

---

### Progress

- **Completed:** 11
- **Pending:** 31
- **Next Target:** Logical instructions (e.g., `ANA`, `ANI`).

---

### How to Contribute

1. Clone the repository.
2. Add or update instruction implementations.
3. Ensure proper flag handling.
4. Update this README checklist to reflect your changes.
5. Submit a pull request!

---

Happy coding!
