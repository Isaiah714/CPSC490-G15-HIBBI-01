# Project Proposal — Constrained Hardware/ECS architecture Game Engine

**Department of Computer Science**
**CPSC 490 Undergraduate Seminar in Computer Science — Proposal for Capstone Project**

**Group 15 — HIBBI-01** · Sponsor: independent
Authors: Padilla, Isaiah (Isaiah714), Qiu, Homan (NomMilk), Ayala, Brian (BrianTheDevGuy), Cole, Brandon (dev-b-cole), Morrell, Isaac (1mphuls3)
Date: 2026-09-22

> **This file is the proposal document, not a README.** Its section numbers,
> titles, and guidance are copied from the course Word template, so it
> converts cleanly for Canvas submission. Write continuous academic prose —
> no task lists, no emoji, no repo jargon.
>
> Each section below opens with the template's own guidance in a quote block.
> **Delete the quote blocks and every 〈bracket〉 before submitting.**
>
> **Getting this into the Word template for Canvas.** The template numbers
> its headings **automatically** (a multilevel list: top-level sections at
> level 1, *Related Work* and *Problem Statements* at level 2). The numbers
> typed below exist so the repo copy is readable and checkable — so when you
> move the text into Word, do not end up with both sets.
>
> The reliable route, and the one most teams should use: **open the course
> template and paste your prose section by section**, leaving Word's own
> numbering to do the numbering. Ten minutes, no surprises.
>
> If you prefer to convert, `pandoc` can do it (install with
> `winget install pandoc`):
>
>     pandoc proposal/proposal.md -o proposal.docx --reference-doc="CPSC 490 Project Proposal Template Fall 2026.docx"
>
> Then in Word: delete the typed `0.` / `1.` / `1.1` prefixes (Word re-adds
> them from the list), and set *Related Work* and *Problem Statements* to the
> template's level-2 heading so they number as 1.1 and 1.2. Check figure
> placement, then submit.
>
> **Formatting requirements — the submitted Word document is graded against
> these, explicitly:**
>
> - **Cover page: use the template's cover page, unchanged in layout.** Fill
>   in only its fields — project title, group number and name, sponsor,
>   authors, date — and keep the template's own placement, fonts and spacing
>   for it. The header block at the top of this file carries the same fields
>   so the paste is a transcription, not a redesign.
> - **Font: Times New Roman, 11-point.** Body text, headings and captions
>   take their size and style from the template's own styles — do not
>   restyle anything by hand.
> - **Line spacing: 1.5.** **Margins: 1.0 inch** on all four sides.
> - **Section format, numbering and indentation must match the Word template
>   exactly** — the multilevel-list numbering, heading levels, and paragraph
>   indentation are the template's, not yours. If your document's §1.1 looks
>   different from the template's §1.1, fix yours.
> - **Length: the Final Project Proposal Paper (due Sun Dec 20) must exceed
>   50 pages** under exactly this formatting — font, spacing and margins are
>   fixed above precisely so page count means the same thing for every team.
>   The Preview paper (due Sun Nov 29) is the same document part-way; it has
>   no minimum, but it is graded on the same formatting.
>
> A paste into the template inherits all of this automatically **if you paste
> as text and let Word's styles apply** (Home → Paste → *Keep Text Only*, or
> apply the template's styles after pasting). A pandoc conversion with
> `--reference-doc` inherits it too — but verify font, spacing and margins
> afterward rather than assuming.
>
> Either way, keep this Markdown copy current — it is what peer review and CI
> can actually read. If your team writes in Word instead, commit the `.docx`
> here as well.

---

## 0. Abstract

Game engines play an important role in modern game development by providing the systems responsible for rendering, resource management, memory handling, and the execution of game logic. However, many existing engines are designed to support a broad range of applications and platforms, which can result in significant resource requirements. This can create difficulties for developers specificly working with resource-constrained hardware. At the same time, the way a game engine organizes and processes its data can have a substantial effect on performance, particularly when a game must manage large numbers of entities simultaneously.

The proposed project is a low-level gameengine built around older hardware with anEntity Component System (ECS) architecture.The engine will provide direct control overfundamental rendering and game systems whileavoiding dependencies on graphics featuresintroduced in later versions of OpenGL. TheECS will organize game data into entities,components, and systems rather than relyingprimarily on traditional object-orientedgame objects. This approach is significantbecause it introduces data-oriented designand improved memory locality while operatingwithin the limitations of an older graphicsAPI. Implementing these systems together isnon-trivial because the engine must balancecompatibility, performance, memorymanagement, and modularity without relyingon modern graphics functionality.
The primary goals of the project are todevelop a functional rendering system,implement an ECS capable of efficientlyprocessing game entities, and create a wayfor user of the applications to create theirown games. The expected outcome is alightweight engine uses modern architecturaltechniques to improve performance whilemaintaining support for legacy hardware. Theproject will also evaluate the performanceand limitations of the ECS architectureapproach through testing and exampleapplications.
The remainder of this document describes the background and motivation for the project, the proposed engine architecture and technologies.

## 1. Introduction

The video game industry is the largest and most profitable entertainment industry in the world and at the very heart of it is the game engine. The large video game studios either create their own custom game engines for their own specific needs, or they use commercial game engines. There are also indie developers, of which the vast majority use these commercial game engines. Most indie developers use low-end/constrained hardware. These commercial game engines are designed to handle a wide range of needs but also come with an overhead of features that require high specs. Traditional game engines use the Object-Oriented Programming (OOP) approach which has its strengths and weaknesses. We will be making a game engine that can be run on constrained hardware and will use the Entity-Component-System (ECS). We will make a game using this game engine that will showcase its use but also test and measure the performance with a lot of the same entities. We all have a love of video games and a passion for making video games. This passion has at times required the ability to purchase higher-end hardware that would otherwise not be required for other fields of computer science. Due to this, we know many others are out there, and many might not have the means to acquire the hardware to use these commercial game engines but still want to follow their passion.

The importance of game engines is far more than just creating games; it sits between the hardware and the logic and manages resources. The game engine implements custom memory allocation instead of standard OS allocations so that data can be grabbed faster. It provides a unified API so that code doesn’t need to be rewritten for every specific device. It manages assets such as textures, 3D models, audio files and more. It also talks to graphics APIs to translate 3D coordinates into 2D pixels on the screen.

Due to the vast number of features commercial game engines have and tasks they are built to do and the traditional engine architecture of OOD, it introduces bloat of features and hardware requirements that most users don’t need. These requirements include modern high-end CPUs, large amounts of ram capacity and memory bandwidth, dedicated GPUs, and large hard drive space.

Entity-Component System architecture uses the Data-Oriented Design (DOD) instead of the OOD which is traditionally used in game engines. This architecture pattern for video games structures code DOD. While the traditional OOP approach has every entity in the world as an object, DOD separates data from logic. DOD just uses IDs and pure data structs. Same type components are stored contiguously and the system logic loops through the arrays sequentially. This helps with lowering hardware requirements.

As game simulations become more complex, the performance of the architecture used to represent and update the game objects within those simulations becomes an important design choice in developing a game. This is especially relevant as the number of entities simulated increases. A single entity may only perform trivial calculations, like updating position, state, AI, or health, when scaled up into the hundreds or thousands, that becomes tons of data the CPU needs to read from and write to every frame.

These performance considerations are specifically relevant on resource constrained hardware, where limited processing and memory resources can make inefficient data access and computations more apparent. Although modern hardware can compensate for inefficient implementations through pure processing power, not all systems have this level of computational headroom. Understanding how software architecture affects performance under these constraints is important to understand game development and the broader study of data oriented design.

The project aims to analyze the performance of an Entity Component System (ECS) architecture when used for an entity dense game running on constrained hardware. Rather than a general purpose game engine, the project will implement a small specialized engine designed to support a single game project, which will act as a controlled environment where a large number of entities could be simulated and the performance can be measured and compared.

The benefits associated with ECS and Data Oriented Design are dependent on the specific workload and implementation of ECS. An architecture that performs well for one type of application or on one type of hardware may provide less benefit under different conditions. The project attempts to measure and evaluate the performance of ECS under an entity heavy game workload, in order to provide insight into when ECS architecture is beneficial and when its advantages may not be significant.

Our project approach differs from general purpose and commercial game engines because it aims to prioritize controlled performance over functionality breadth. While those commercial engines need to implement all functions necessary to support many types of games, platforms, and even other non-game r, our engine will implement only the systems needed to support our game and workload. This allows us to focus on the ECS architecture itself, in order to maintain and measure performance levels necessary for resource constrained hardware conditions. The final product will consist of a functional game which functions as a demonstration and repeatable workload to benchmark and analyze the performance of ECS architecture.

### 1.1 Related Work

| Existing approach | What it does | Pros | Cons | Why ours differs |
|---|---|---|---|---|
| Unity [1] | General game engine with advanced features such as pathfinding. | Extremely feature rich, well documented and supported. | More bloated compared to other frameworks. | It would be more optimized due to Unity having to support multiple hardware. In addition, our engine would be more leaner and in theory take up less space than Unity. |
| Flecs [2] | Lightweight ECS framework library | Feature rich ECS implementation, archetype storage | Does not implement game engine functionality itself | Combine ECS system with rendering, input, and other infrastructure to develop a  |
| EnTT [3] | Lightweight C++ ECS library | Simple API, flexible component management | Does not implement game engine functionality itself | Combine ECS system with rendering, input, and other infrastructure to develop a game |
| MonoGame [4] | Code first game development framework, including graphics, audio, and input | Flexible, relatively low level | Developers may need to implement additional tooling for their project | A more integrated ECS based runtime and lightweight editor and tooling foundation |

There are currently many different general use engines that developers can currently take advantage of such as Unity, Unreal, and Godot. These engines are aimed to be versatile and are able to be compiled to multiple different platforms, with Unity able to complied to 17 different platforms [1]. Ours will be different in that it would be targeted towards low-end and old 64-bit x86-64 processors around the late 2000’s range. By narrowing our scope we are able to create a much more performant game compared to those offered by general use engines. As the more compatible an engine is the more they have to give up in storage and performance.
Frameworks like MonoGame also offer an alternative to full fledged game engine and editor applications like Unity. The tool provides developers foundational game programming capabilities while allowing more control over structure and implementation [2]. That flexibility can be valuable to developers who want a code first workflow, or want to avoid features they do not need in their project. However, developers may need to implement additional systems for a complete game development workflow, such as a visual scene editor which MonoGame does not include by default. Our proposed engine project aims to create a more integrated runtime and foundation without resource intensive tooling of a general purpose game engine.
ECS frameworks can be a more direct comparison to our project. Libraries like Flecs and EnTT provide ECS functionality that can be integrated into larger applications and provide developers flexibility in constructing their own systems around them [3], [4]. However, an ECS library on its own doesn’t provide the systems required to create a fully functioning game. Developers would still need to implement rendering functionality, input system, resource loading, and more. Our project would reduce the burden of integration by combining ECS systems with foundational game engine functionality and services for developers to build off of.

### 1.2 Problem Statements

| Problem | Addressed by |
|---|---|
| P1 Giving the developers an idea of the core features in the proposed game development framework can be challenging, particularly when showcasing its rendering capabilities, interactive gameplay, and world creation features. A functional demo is needed to validate the framework's usability, demonstrate its performance, and illustrate what developers can achieve in our proposed engine. | Game Demo (#n) |
| P2 Developers looking for lightweight adaptable game development frameworks face trade-offs with lower level tools that may require substantial custom implementation and comprehensive game engines that provide more functionality than necessary for a project. This creates a need for a framework that supports efficient game development, cross platform compatibility, flexible rendering, and accessible world creation | Game Engine (#n) |

## 2. Goals and Objectives

- **Goal 1: 〈Game Demo〉** [epic:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/25]
  - Objective 1.1: Implement engaging enemies for players to interact with [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/26]
  - Objective 1.2: Create a gameplay loop for a fun and interactive user experience [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/27]
  - Objective 1.3: Implement player inputs and level interaction [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/28]
  - Objective 1.4: Design and implement immersive world building [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/29]
- **Goal 2: 〈Game Engine〉** [epic:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/24]
  - Objective 2.1: Implement ECS architecture for the engine. [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/30]
  - Objective 2.2: Demonstrate multiplatform compilation. [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/31]
  - Objective 2.3: Create an adaptable real time render system. [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/32]
  - Objective 2.4: Implement visual editor to import models, create objects, and design the game world. [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/33]

## 3. Proposed Approaches

> Describe your proposed approach to solve the problem, specifying how you
> will achieve the stated goals. List some possible strategies.

〈Your approach — **clear and concise**. State the strategy you chose, the
alternatives you considered, and the reasoning that decided between them.
Think of this as the argument, not the manual: a reader should finish this
section understanding *what* you will do and *why that* rather than the
alternatives.〉

**Keep the details out of this section.** Tooling, platforms, frameworks,
DBMS choices, environment setup, diagrams, and the work breakdown all belong
in §4 (Required Environment, Resources, and Planned Activities). If a
sentence here names a version number, a library, or a configuration, it
probably belongs in §4 — leave a pointer instead ("the implementation stack
is detailed in §4").

〈A few paragraphs, or a short list of candidate strategies with one line of
trade-off each. If it runs past a page, you are writing §4.〉

## 4. Required Environment, Resources, and Planned Activities

> Review the required and available resources and environment to complete
> your project. For example, server, platform, software tools, operating
> systems, DBMS, or any required skills.
>
> Describe the expected activities to achieve the stated goals, e.g.,
> software development process.

〈Your environment, resources, and planned activities.〉

**Diagrams belong in this section.** Include at minimum a high-level
architecture diagram and a system (context) diagram; add the ER/EER model and
a data-flow diagram where they help the reader understand what you are
building and what it depends on. Draw them with any graphical tool
(Lucidchart, draw.io, Miro, Mermaid, ERDPlus, Figma), keep the authoritative
copies in `docs/design/` with both editable source and exported image, and
reference them here.

〈Number every figure, caption it, and point at it from the prose — "Figure 1
shows the three deployment tiers and the trust boundary between them." A
figure the text never mentions is decoration. See `docs/design/DIAGRAMS.md`
for tools, conventions, and the rule that every box and arrow must be
verified against reality.〉

### Specification and design documents

**Every specification and design document the team writes is listed here**
with the objective it serves. This section is the index of the project's
technical detail: §3 holds the argument, §4 holds the documents that make it
buildable. CI gate G9 fails if a document exists in `docs/specs/` or
`docs/design/` that this section does not link.

| Document | Kind | Covers | Issues |
|---|---|---|---|
| 〈docs/specs/account-management.md〉 | specification | 〈account management requirements〉 | 〈#n, #n〉 |
| 〈docs/design/architecture.md〉 | design | 〈system architecture + data model〉 | 〈#n〉 |

〈The scaffold ships `docs/specs/example-spec.md` and
`docs/design/example-design.md` as worked examples — read them, then delete
them once you have your own, and list yours here.〉

〈Replace these rows with your own. Each document names its epic and stories
in its own first lines too (gate G2), so the trail runs both ways.〉

### Planned activities — the work items

The goals and objectives live in §2 as epics and user stories. **This section
links every *other* work item: features, enhancements, bugs, tasks, and
sub-tasks** — the concrete activities that deliver those objectives. CI gate
G8 fails if such an issue exists that this section does not link.

| Issue | Type | Activity | Parent | Owner | Sprint |
|---|---|---|---|---|---|
| 〈#9〉 | 〈task〉 | 〈Window and Renderer〉 | [story:https://github.com/Isaiah714/CPSC490-G15-HIBBI-01/issues/32] | 〈Isaiah〉 | 〈Sprint 2〉 |


〈Replace these rows with your own, and keep the table current as you file new
issues — with §2 it gives a reader every planned activity in one place, each
traceable to the objective it serves.〉

## 5. Project Outcomes

> Describe the outcomes or deliverables, e.g., final project report, user
> manuals, source code, data or database files, etc.
>
> Note: the deliverables always include the team GitHub repository, which
> must already contain prototype v0 (a thin end-to-end proof-of-concept,
> however small, running when this proposal is submitted). Briefly describe
> what your v0 demonstrates and how to run it.

〈**One or two paragraphs** explaining the project outcome overall — what will
exist when the project is finished, and what it will let someone do. Keep it
prose, not a checklist; name the deliverables inside the paragraphs, and say
briefly what prototype v0 demonstrates today and how to run it.〉

## 6. Project Timeline

> Identifies tasks (project objectives) to be performed, milestones to be
> met, and the estimated number of hours for each task.

〈**This is the plan for CPSC 491 next semester — the implementation timeline,
not this semester's proposal work.** Identify the tasks (your objectives from
§2), the milestones, and the estimated hours for each, in the order they will
be built. State the assumptions it rests on (sponsor availability, data
access, hardware).〉

| Task (objective) | Milestone | Owner | Est. hours | Spring phase |
|---|---|---|---|---|
| 〈…〉 | 〈…〉 | 〈…〉 | 〈…〉 | 〈…〉 |
| 〈…〉 | 〈…〉 | 〈…〉 | 〈…〉 | 〈…〉 |

〈Do **not** put this fall's four proposal sprints here — those live on the
project board and in `docs/sprint-reviews/`. This section answers "how does
the system actually get built next semester?"〉

## 7. AI Usage

> Per the course AI policy (see the syllabus, Use of AI Tools), disclose the
> AI tools used in preparing this proposal and the prototype: which tools,
> for what tasks (e.g., code generation, test writing, debugging,
> diagramming), and approximately what fraction of each artifact was
> AI-assisted.
>
> Reminder: the prose of this proposal must be your own writing. You remain
> fully responsible for the correctness of all AI-assisted work, including
> the prototype code.

〈Your disclosure. Naming the tool is not disclosure — name what it drafted,
what fraction of each artifact was AI-assisted, and how you verified it.〉

## 8. References

[1] https://www.gamesindustry.biz/what-is-the-best-game-engine-is-unity-the-right-game-engine-for-you. Oct 11, 2026
[2] https://monogame.net/. Oct 11, 2026
[3] https://www.flecs.dev/flecs/. Oct 11, 2026
[4] https://github.com/skypjack/entt. Oct 11, 2026