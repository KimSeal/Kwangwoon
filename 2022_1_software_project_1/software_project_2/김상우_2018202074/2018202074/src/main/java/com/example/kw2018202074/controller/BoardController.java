package com.example.kw2018202074.controller;
import com.example.kw2018202074.domain.Board;
import com.example.kw2018202074.service.BoardService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
//import functions that used in BoardController
@Slf4j          //annotation about logging framework
@Controller     //controller annotation
public class BoardController {  //controller class
    private BoardService service;   //service variable to take data to make controller
    public BoardController(BoardService boardService) {
        this.service = boardService;
    }
    //setter
    @GetMapping("/")                //about http://localhost:8080/
    public String init(Model model){
        model.addAttribute("list", service.boardList());    //to take all datas about database
        model.addAttribute("page", 0);          //current page = 0(1)
        return "/boards/start";                                         //go to start
    }

    @GetMapping("/board/start")     //about http://localhost:start
    public String start(Model model, int page){                        //when start html
        model.addAttribute("list", service.boardList());   //to take all data about database
        model.addAttribute("page", page);                   //take page from current variable
        return "/boards/main";                                          //go to main.html
    }

    @GetMapping("/board/main")                                      //when take /board/main
    public String main(Model model){                                    //when go to main html
        model.addAttribute("list", service.boardList());    //to take all datas about database
        model.addAttribute("page", 0);          //current page is zero(when end of upload)
        return "/boards/main";                                          //go to main.html
    }
    @GetMapping("/board/view")                                      //when take /board/main
    public String viewBoard(Model model, Long boardId){                 //when go to view html
        service.updateView(boardId);                                     //update view about board that have spectiboardId
        model.addAttribute("view",service.getBoard(boardId));//find and put board into view.html
        return "/boards/view";                                          //go to view.html
    }
    @GetMapping("/board/upload")                                     //when take /board/upload
    public String uploadBoardForm(){
        return "/boards/upload";
    }       //go to upload.html

    @PostMapping("/board/upload")                                   //end of /board/upload
    public String uploadBoard(Board board){                            //when we need to upload board
        service.uploadBoard(board);                                     //do upload board
        return "redirect:/board/main";                                  //go back to main
    }
    @PutMapping("/board/update")                                    //when go to update
    public String updateBoard(Board board){                             //when we need to update board
        service.updateBoard(board);                                     //update current board
        return "redirect:/board/main";                                  //go back to main
    }

    @DeleteMapping("/board/delete")                                 //when go to delete to delete board
    public String deleteBoard(Long boardId){                            //when we need to delete board
        service.deleteBoard(boardId);                                   //delete current board
        return "redirect:/board/main";                                  //go back to main
    }
}
