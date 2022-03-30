set(sources main.cpp 
            board.cpp 
            cell.cpp 
            board.hpp 
            cell.hpp
            gol_window.cpp
            gol_window.hpp
            board_window.cpp
            board_window.hpp )
            
target_sources(${PROJECT_NAME} PRIVATE ${sources})

