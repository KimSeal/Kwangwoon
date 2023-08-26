package com.example.kw2018202074.domain;
import lombok.*;
import javax.persistence.*;
//import to use java persistence and lombok
@Getter     //annotation to get function auto
@Entity     //mapping to table
@Setter     //annotation to set function auto
@NoArgsConstructor //make Constructor
@AllArgsConstructor//make Constructor that take every field value
@Table(name="BOARD")   //to use table
public class Board {
    @Id                                                 //boardId is main ket
    @GeneratedValue(strategy = GenerationType.IDENTITY) //we use DataBase's identity column
    private Long boardId;                               //main key variable
    private String title;                               //title of board
    private String content;                             //contents of board
    private String name;                                //upload or update time of board
    private int read;                                   //views of board

    @Builder                                            //make builder auto
    public void BoardEntity(String title, String content, String name, int read){
        this.title = title;
        this.content=content;
        this.name=name;
        this.read=read;
    }
}
