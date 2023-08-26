package com.example.kw2018202074.mapper;
import com.example.kw2018202074.domain.Board;
import org.springframework.stereotype.Repository;
import java.util.List;

@Repository                     //repository annotation
public interface BoardMapper {  //interface to define functions
    List<Board> getList();      //function to change boards to list
    Board getBoard(Long boardId);//search and take board that have this boardId
    void uploadBoard(Board board);//upload board to database
    void updateBoard(Board board);//update board in database
    void deleteBoard(Long boardId);//delete board in database
    int updateView(Long boardId);//plus 1 about view

}
