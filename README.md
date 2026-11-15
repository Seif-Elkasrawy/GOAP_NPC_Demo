# GOAP NPC Plugin DEMO — Fork Notice

This is a fork of [narratech/GOAP_NPC_Demo](https://github.com/narratech/GOAP_NPC_Demo), used as the evaluation/test harness for my Master's thesis on improving the GOAP_NPC plugin under the Master's in Visual Informatics program at Faculty of Informatics, Masaryk University. Ported to run on Unreal Engine 5.7. The original README below is preserved unmodified for reference and attribution.

Seifeldin Elkasrawy ~ Student at MUNI

---

# GOAP NPC Plugin DEMO

Hi there!

We are a group of students from the Faculty of Computer Science at the Complutense University of Madrid. We have developed, as part of our final degree project, a plugin for Unreal Engine 4 called GOAP NPC. This plugin aims to help with the creation of Artificial Intelligence on Non-Player Characters, based on using a Goal Oriented Action Planning (GOAP) architecture.

Most developers usually use Behavior Trees to decide what the NPCs can do. It is very intuitive and easy to get started with. However, as the complexity of the scenario grows, it becomes really hard to handle. That's when GOAP comes into play. One of the most important differences with Behavior Trees is the ability of GOAP to react to external changes and dynamically modify the plan during runtime. You can obtain more information about GOAP [here](http://alumni.media.mit.edu/~jorkin/GOAP_draft_AIWisdom2_2003.pdf).

Currently we are contacting developers who have a minimum of knowledge about developing videogames with Blueprints on Unreal Engine to ask for help in testing our tool and sharing their experience. The test involves the creation by the developer of a simple controller for a NPC with a few actions and both kind of planners (first with Behavior Trees, and then using GOAP). You can access the survey [here](https://forms.gle/i9UivkxC117v6Eci8).

We greatly appreciate the help that you can provide us. It will be very useful to contribute to the improvement of our plugin, and to help everyone to better understand the usefulness of AI planning tools. If you have any questions or want to know more about it, please contact us by [email](info@narratech.com).

Thank you very much!
- Diego Romero, Mario Sanchez & Jose Manuel Sierra

## To open the project

1. Right click on the .uproject file and choose the "Generate Visual Studio project files" option.
2. Wait for the .sln file to be generated and run it.
3. While everything is loading in Visual Studio, you can open the project in Unreal or launch from VS.
  1. Right click on the .uproject file and choose the "Generate Visual Studio project files" option.
  2. Wait for the .sln file to be generated and run it.
  3. While everything is loading in Visual Studio, you can open the project in Unreal or launch from VS.

## Controls and debugging (thesis fork)

Added for the cooperative multi-agent showcase. The keys work in Play In Editor.

| Key | Action |
|---|---|
| K | Destroy the GOAP agent nearest to the player (pawn and controller). The squad coordinator reassigns its task. |
| J | Jam or unjam the key door nearest to the player. Agents are not told: they find out when `OpenDoor` fails. |
| G | Cycle debug drawing: off, compact, full. |
| H | Reload the current level (resets the scenario). |
| P | Add a test task with priority 20 to the squad coordinator at runtime. With preemption enabled it takes an agent from a lower-priority task. |
| C | Reset the goal of the failure-test agent (failure-test level only). |
| Z / X | Original demo hotkeys: set the goal to Get Coin / Follow Character (single-agent demo). |

Console commands (type in the console with `~`):

- `DestroyPawnByName <name> [true]` destroys the first pawn whose name contains the text. The optional flag also destroys its controller.
- `SetDoorJammed <door name> <true|false>` jams or unjams a key door by name.

### Console variables

| Variable | Default | Effect |
|---|---|---|
| `GOAP.DebugDraw` | 0 | 0 off. 1 status label above each agent and a marker at each squad task. 2 adds current action and step, failure count, goal and a line to the target. |
| `GOAP.EventDrivenReplanning` | 1 | 1 replans only on events. 0 replans on every `executeGOAP` call (baseline for comparison). |
| `GOAP.LogSquad` | 0 | Logs coordinator events: assignment, preemption, completion, handback, failure, retry,