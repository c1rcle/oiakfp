#pragma once

#include <iostream>
#include <vector>

class ByteArray
{
public:
    ///ByteArray static class default constructor.
    ByteArray() = default;
    /// Copies bytes to a container.
    /// \param source - source byte array.
    /// \param size - array element count.
    /// \param destination - destination vector.
    static void putBytes(const u_char * source, u_int size, std::vector<u_char> &destination);
    /// Sets specified bit value.
    /// \param byte - specific byte which value will change.
    /// \param position - position in range <0;7>.
    /// \param value - new value.
    static void setBit(u_char &byte, u_int position, bool value);
    /// Returns specified bit value.
    /// \param byte - specific byte which value will be retrieved.
    /// \param position - position in range <0;7>.
    /// \return true if bit equals 1, otherwise false.
    static bool getBit(u_char &byte, u_int position);
    /// Shifts a vector of bytes 'shift' times right.
    /// \param vector - vector which contents are going to be shifted.
    /// \param shift - bit shift count.
    static void shiftVectorRight(std::vector<u_char> &vector, int shift);
    /// Shifts a vector of bytes 'shift' times left.
    /// \param vector - vector which contents are going to be shifted.
    /// \param shift - bit shift count.
    static void shiftVectorLeft(std::vector<u_char> &vector, int shift);
    /// Adds bytes from two containers together (result stored in first).
    /// \param first - first addition operand (vector).
    /// \param second - second addition operand (vector).
    /// \return 0 - if there is no carry, 1 - otherwise.
    static bool addBytes(std::vector<u_char> &first, std::vector<u_char> &second);
    /// Subtracts bytes from two containers (result stored in first).
    /// \param first - first subtraction operand (vector).
    /// \param second - second subtraction operand (vector).
    /// \return 0 - if there is no carry, 1 - otherwise.
    static bool subtractBytes(std::vector<u_char> &first, const std::vector<u_char> &second);
    /// Comparision subtracts second argument from first.
    /// \param first - byte array for comparision.
    /// \param second - byte array for comparision.
    /// \return 0 if first and second argument is the same, -1 if second is greater and 1 if first is greater.
    static int compare(const std::vector<u_char> &first, const std::vector<u_char> &second);

    static bool checkIfZero(const std::vector<u_char> &first);
};

std::ostream& operator <<(std::ostream& str, const std::vector<u_char>& obj);