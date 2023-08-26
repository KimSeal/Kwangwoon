package com.example.kw2018202074;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
//import to execute
@SpringBootApplication  //application about spring
@MapperScan(basePackages = "com.example.kw2018202074") //scan package in this project
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
    //program start
}
