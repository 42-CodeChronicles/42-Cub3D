# 🚪 DOORS - Simple Explanation for Everyone!

## What is a Door?

A door is a special wall that can OPEN and CLOSE! Just like the door in your bedroom - sometimes it's closed and you can't walk through it, and sometimes it's open and you can!

---

## 📂 Files that Handle Doors

### 1. **cub3D.h** - The Door Recipe

This tells the computer how to remember doors:

```c
typedef struct s_door
{
	int				x;           // Door's position left-right on the map
	int				y;           // Door's position up-down on the map
	int				is_open;     // Is the door open? (1 = yes, 0 = no)
	double			open_amount; // How much is it open? (0.0 to 1.0)
}	t_door;
```

**Simple Explanation:**
- `x` and `y` = Where the door is on the map (like saying "the door is in room 5")
- `is_open` = Is someone opening it? (yes or no)
- `open_amount` = How far open is it? 
  - 0.0 = Completely closed
  - 0.5 = Half open
  - 1.0 = Fully open

**Real-Life Example:**
Think of your bedroom door:
- Position (x, y): "My door is at the bedroom entrance"
- is_open: "Am I opening it right now?"
- open_amount: 0.0 (closed), 0.5 (halfway), 1.0 (wide open)

---

### 2. **doors.c** - The Door Manager

This file creates and manages all the doors in your game!

#### Function: `count_doors()` - Count How Many Doors

```c
static int	count_doors(t_config *data)
{
	int	count;
	int	x;
	int	y;

	count = 0;  // Start counting from zero
	y = 0;
	while (y < data->map.height)  // Go through each row
	{
		x = 0;
		while (x < data->map.width)  // Go through each column
		{
			if (data->map.array_map[y][x] == 'D')  // Found a door!
				count++;  // Add 1 to our count
			x++;
		}
		y++;
	}
	return (count);  // Tell how many doors we found
}
```

**Simple Example:**
Imagine you're walking through your house counting doors:
- Living room: 1 door
- Kitchen: 2 doors
- Bedroom: 1 door
- Total: 4 doors!

This function does the same thing, but for your game map!

---

#### Function: `populate_doors()` - Set Up All the Doors

```c
static void	populate_doors(t_config *data)
{
	int	door_index;
	int	x;
	int	y;

	door_index = 0;  // Which door are we setting up? (first, second, third...)
	y = 0;
	while (y < data->map.height)  // Look through whole map
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.array_map[y][x] == 'D')  // Found a door!
			{
				// Remember where this door is
				data->doors[door_index].x = x;
				data->doors[door_index].y = y;
				
				// Doors start closed
				data->doors[door_index].is_open = 0;
				data->doors[door_index].open_amount = 0.0;
				
				door_index++;  // Move to next door
			}
			x++;
		}
		y++;
	}
}
```

**Simple Example:**
Think of building LEGO doors:
1. Find where each door should go
2. Put the door there
3. Make sure it starts closed
4. Remember its position so you can open it later!

---

#### Function: `load_door_texture()` - Get the Door Picture

```c
static void	load_door_texture(t_config *data)
{
	// Load the door picture from a file
	data->door_texture = mlx_load_png("./textures/door.png");
	
	if (!data->door_texture)  // Uh oh, couldn't find the picture!
	{
		printf("Error: Can't load Door texture\n");
		// Use the north wall picture instead
		data->door_texture = data->no_texture;
	}
}
```

**Simple Explanation:**
This is like finding a picture of a door to put on your door!
- If we find the door picture: Great! Use it!
- If we can't find it: Use a wall picture instead so the game doesn't crash

---

#### Function: `init_doors()` - The Main Door Setup

```c
void	init_doors(t_config *data)
{
	// First, count how many doors we have
	data->door_count = count_doors(data);
	
	// If there are no doors, we're done!
	if (!data->door_count)
	{
		data->doors = NULL;
		return ;
	}
	
	// Make space in memory to remember all the doors
	data->doors = malloc(sizeof(t_door) * data->door_count);
	
	if (!data->doors)  // Couldn't make space!
	{
		printf("Error: Can't allocate memory for doors\n");
		return ;
	}
	
	// Set up each door
	populate_doors(data);
	
	// Load the door picture
	load_door_texture(data);
}
```

**Step-by-Step:**
1. **Count:** "How many doors do I have?"
2. **Make Space:** Create room to remember all doors
3. **Set Up:** Configure each door (position, closed state)
4. **Load Picture:** Get the door image

**Real-Life Example:**
Like organizing your toy collection:
1. Count how many toys you have
2. Get a toy box big enough for all of them
3. Put each toy in the box and remember where it is
4. Put pictures on the box so you know what's inside!

---

#### Function: `check_door()` - Is There a Door Here?

```c
int	check_door(t_config *data, int x, int y)
{
	int	i;

	// If we don't have any doors, answer is no
	if (!data->doors)
		return (0);
	
	i = 0;
	// Check each door we have
	while (i < data->door_count)
	{
		// Is this door at position (x, y)?
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (1);  // Yes! There's a door here!
		i++;
	}
	return (0);  // No door found here
}
```

**Simple Example:**
You ask: "Is there a door at the entrance to my bedroom?"
The function looks at all doors and says:
- "Door 1 is in the living room - nope"
- "Door 2 is in the kitchen - nope"
- "Door 3 is at the bedroom entrance - YES! Found it!"

---

### 3. **texture_helper.c** - Finding Door State

#### Function: `get_door_state()` - Get Door Information

```c
t_door	*get_door_state(t_config *data, int x, int y)
{
	int	i;

	// If no doors exist, return nothing
	if (!data->doors)
		return (NULL);
	
	i = 0;
	// Look at each door
	while (i < data->door_count)
	{
		// Is this the door we're looking for?
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);  // Yes! Give me all its information
		i++;
	}
	return (NULL);  // Didn't find that door
}
```

**Simple Explanation:**
This is like asking: "Tell me everything about the door at position (x, y)"
It returns all the door's information:
- Is it open?
- How much is it open?
- Where is it?

---

## 🎮 How Doors Work in Your Game

### Complete Example:

Let's say you want to open a door!

#### Step 1: Find the Door
```c
t_door *my_door = get_door_state(data, 5, 3);
// "Get me the door at position (5, 3)"
```

#### Step 2: Open the Door
```c
if (my_door)
{
	my_door->is_open = 1;        // Start opening!
	my_door->open_amount = 0.0;  // Currently closed
}
```

#### Step 3: Watch it Open (this happens over time)
```c
// Frame 1: open_amount = 0.1  (starting to open)
// Frame 2: open_amount = 0.2  (opening more)
// Frame 3: open_amount = 0.5  (halfway!)
// Frame 4: open_amount = 0.8  (almost there)
// Frame 5: open_amount = 1.0  (fully open!)
```

#### Step 4: When Drawing the Door
```c
// In texture.c, init_tex_data():
door_offset = door->open_amount;  // How much is door open?
pos->wall_x += door_offset;        // Shift the texture

// This makes the door "slide" open!
```

---

## 🎨 Visual Example

Imagine looking at a door opening:

### Closed Door (open_amount = 0.0):
```
+-------+
|   D   |  <- You see the full door
|   O   |
|   O   |
|   R   |
+-------+
```

### Half Open (open_amount = 0.5):
```
+-------+
|  D |  |  <- Door texture is shifted
|  O |  |     You can start to see through!
|  O |  |
+-------+
```

### Fully Open (open_amount = 1.0):
```
+-------+
| |     |  <- Door is completely to the side
| |     |     You can walk through!
| |     |
+-------+
```

---

## 🔑 Important Terms

- **Door Position (x, y):** Where the door is on the map
- **is_open:** Is the door currently opening or closing?
- **open_amount:** A number from 0.0 (closed) to 1.0 (open)
- **door_texture:** The picture of the door
- **door_offset:** How much to shift the door's picture when it opens

---

## 🏗️ How Doors Work with Textures

When you draw a door, the code does something clever:

```c
// Normal wall: Just draw the texture
tex_x = (int)(wall_x * texture->width);

// Opening door: Shift the texture!
wall_x += door->open_amount;  // Add the opening amount
tex_x = (int)(wall_x * texture->width);
```

**What This Does:**
- Closed door (0.0): Texture is normal
- Opening door (0.5): Texture shifts halfway - you start seeing through
- Open door (1.0): Texture shifts completely - door is "gone"

It's like sliding a piece of paper across your desk - the door texture slides to show the opening!

---

## 🎯 Summary

Doors in your game are special walls that can:
1. **Be Found:** The game searches the map for 'D' symbols
2. **Be Created:** Each door gets a position and starting state (closed)
3. **Be Opened:** The open_amount increases from 0.0 to 1.0
4. **Be Drawn:** The door texture shifts based on how open it is
5. **Be Checked:** You can ask "is there a door here?" and "how open is it?"

Think of it like this: Every door is a wall with a special superpower - it can slide to the side to let you through! 🚪✨
