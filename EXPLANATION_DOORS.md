# 🚪 DOORS EXPLAINED (For 10 Year Olds!)

## What is a Door?

A **door** is like a special wall that can open and close! Just like the doors in your house - you can walk through them when they're open, but they block you when they're closed.

---

## 📁 File About Doors

### **doors.c** - The Door Manager

This file handles everything about doors in your game!

---

## 🎯 The Main Functions

### 1. **`count_doors()`** - Counts How Many Doors You Have

**What it does:**
- Looks at your entire map
- Counts every 'D' it finds (D = Door)
- Returns the total number

**Example:**
```
Your map looks like:
1111111
1000D01
1000001
1D00001
1111111

This function would say: "I found 2 doors!"
```

**How it works:**
```c
Go through every row (y)
  Go through every column (x)
    If we find a 'D' → count = count + 1
Return count
```

---

### 2. **`populate_doors()`** - Remembers Where All Doors Are

**What it does:**
- Goes through the map again
- For each door it finds, it saves:
  - Where is it? (x and y position)
  - Is it open or closed? (starts closed)
  - How much is it open? (starts at 0%)

**Example:**
```
Door 1 is at position (4, 1)
  - x = 4 (column 4)
  - y = 1 (row 1)
  - is_open = 0 (closed)
  - open_amount = 0.0 (0% open)

Door 2 is at position (1, 3)
  - x = 1 (column 1)
  - y = 3 (row 3)
  - is_open = 0 (closed)
  - open_amount = 0.0 (0% open)
```

**Think of it like a list:**
```
📝 Door List:
   Door #0: At (4,1), Closed, 0% open
   Door #1: At (1,3), Closed, 0% open
```

---

### 3. **`load_door_texture()`** - Gets the Door Picture

**What it does:**
- Loads the door image from `textures/door.png`
- If it can't find the image, it uses the North wall texture instead

**Example:**
```
Computer tries to load "door.png"
Success! → Use the cool door texture 🚪
Failed! → "Oops! I'll use the wall texture instead"
```

---

### 4. **`init_doors()`** - The Boss Function That Sets Everything Up

**What it does (step by step):**

**Step 1:** Count all the doors
```
"How many doors do we have? Let me count... We have 2 doors!"
```

**Step 2:** If no doors found
```
"No doors? Okay, I won't do anything!"
```

**Step 3:** Make space to remember all doors
```
"I need to remember 2 doors, so I'll make a list with 2 spots"
```

**Step 4:** Fill in the door information
```
"Now let me go through the map and write down where each door is"
```

**Step 5:** Load the door picture
```
"Finally, let me load the door texture image"
```

---

### 5. **`check_door()`** - Checks if Something is a Door

**What it does:**
- You give it a position (x, y)
- It checks: "Is there a door at this position?"
- Returns: YES (1) or NO (0)

**Example:**
```
Question: "Is there a door at position (4, 1)?"
Answer: "YES! That's Door #0!"

Question: "Is there a door at position (2, 2)?"
Answer: "NO! That's just empty space."
```

**How it works:**
```c
Look through all the doors in our list
  If door.x == x AND door.y == y
    → YES! Found it! Return 1
End of list
→ NO door found. Return 0
```

---

## 📝 Important Data Structure

### `t_door` - Information About One Door

```c
struct t_door {
    int x;              // Column position (left-right)
    int y;              // Row position (up-down)
    int is_open;        // Is it open? 0=No, 1=Yes
    double open_amount; // How much is it open? (0.0 to 1.0)
}
```

**Think of it like this:**
```
📋 Door Information Card:
   Location: Column 4, Row 1
   Status: CLOSED ❌
   Open Amount: 0% (door is fully closed)
```

---

## 🎮 How Door Opening Works (The Visual)

Doors can slide open! The `open_amount` tells how much:

```
open_amount = 0.0  (0%)  → |🚪|  Fully CLOSED
open_amount = 0.25 (25%) → |🚪|  Opening...
open_amount = 0.5  (50%) → | 🚪| Half open
open_amount = 0.75 (75%) → |  🚪| Almost open
open_amount = 1.0  (100%)→ |   | Fully OPEN!
```

When the door opens, the texture slides to show more of the wall behind it!

---

## 🔄 Complete Flow - What Happens When Game Starts

### Step-by-Step:

**1. Game starts loading the map**
```
Reading map file...
Found this:
11111
1D0D1
11111
```

**2. Game calls `init_doors(data)`**

**3. `count_doors()` counts**
```
"I see 2 'D' letters, so 2 doors!"
```

**4. Memory is allocated**
```
"Making a list that can hold 2 door cards"
```

**5. `populate_doors()` fills the information**
```
Door Card #0:
  - Position: (1, 1)
  - Closed
  - 0% open

Door Card #1:
  - Position: (3, 1)
  - Closed
  - 0% open
```

**6. `load_door_texture()` loads the image**
```
"Loading door.png... Success! ✅"
```

**7. Done!**
```
"All doors are set up and ready!"
```

---

## 🎯 Real Game Example

### Scenario: You're Walking Toward a Door

**Before:**
```
You: 👤        Door: |🚪| (closed)
               Position: (5, 5)
               open_amount = 0.0
```

**You press a button to open it:**
```
- Game finds the door at (5, 5)
- Starts opening: open_amount = 0.0 → 0.1 → 0.2 → ... → 1.0
- Door slides open!
```

**After:**
```
You: 👤        Door: |   | (open)
               Position: (5, 5)
               open_amount = 1.0
```

**Now you can walk through!**

---

## 🌟 Summary in Simple Words

**Doors are special walls that can open!**

The door code does these jobs:
1. 🔍 **Finds** all doors in your map (looks for 'D')
2. 📝 **Remembers** where each door is located
3. 🎨 **Loads** the door picture (texture)
4. 🚪 **Tracks** if each door is open or closed
5. 📊 **Knows** how much each door is open (0% to 100%)

**Why is this cool?**
- You can have locked areas
- Doors can slide open smoothly
- Makes the game more realistic
- You can open/close doors by pressing buttons

It's like having automatic sliding doors in a supermarket, but in your game! 🏪✨
