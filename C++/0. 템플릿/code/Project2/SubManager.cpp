#pragma once
#include "electronicManager.h"

/**
* 이 함수는 파일에 기록된 정보를 읽고 상품목록에 추가합니다
*/
//Init()


/**
* 이 함수는 신규 상품을 생성하고 상품목록에 추가합니다.
*
* 사용자가 입력한 정보를 통해 상품을 생성합니다.
* 생성된 상품을 상품목록에 추가합니다.
*/
//Input()


/**
* 이 함수는 현재 상품목록을 출력합니다.
*
* 저장된 상품목록을 모두 출력합니다.
*/
//Print()


/**
* 이 함수는 저장된 상품목록을 파일에 저장합니다.
*
* 저장된 상품목록 객체를 직렬화 후 문자열로 변경하여 파일에 문자열로 저장합니다.
* 저장 성공 여부를 반환합니다.
*
* 반환
*   bool: 저장 성공시 true 반환
*/
//Save()


/**
* 이 함수는 저장된 특정문자열과 상품목록들의 이름 또는 특정 값과 포함 여부를 확인합니다.
*
* 파라미터
*   String searchText: 비교할 문자열입니다.
*
* 반환
*   List<Product*>*: 상품목록중 비교문자열이 포함되는 상품목록
*/
//Search();
