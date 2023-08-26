//import to use some instructions to make BoardService
package com.example.kw2018202074.service;
import com.example.kw2018202074.domain.Board;
import com.example.kw2018202074.mapper.BoardMapper;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import java.util.List;

@Service //chang to Bean and put them in root container(calculate java logic)
public class BoardService {
    private final BoardMapper boardMapper;
    //to use repository
    public BoardService(BoardMapper boardMapper){
        this.boardMapper = boardMapper;
    }
    //setter
    public List<Board> boardList(){return boardMapper.getList();}
    //variable to take all data
    public Board getBoard(Long boardId){return boardMapper.getBoard(boardId);}
    //find board(use boardId)
    @Transactional
    public void uploadBoard(Board board){
        boardMapper.uploadBoard(board);
    }
    //make new board and upload that in data base
    @Transactional
    public void updateBoard(Board board){boardMapper.updateBoard(board);}
    //find board and change data
    @Transactional
    public void deleteBoard(Long boardId){
        boardMapper.deleteBoard(boardId);
    }
    //find board and delete that
    @Transactional
    public int updateView(Long boardId){
        return boardMapper.updateView(boardId);
    }
    //update view by click
}

