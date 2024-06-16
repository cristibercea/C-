#pragma once

class Tests {
public:
	/// <summary>
	/// runs all tests
	/// </summary>
	void run_all() const;

private:
	/// <summary>
	/// domain tests
	/// </summary>
	void test_entity() const;

	/// <summary>
	/// validator tests
	/// </summary>
	void test_validator() const;

	/// <summary>
	/// in-memory repo tests
	/// </summary>
	void test_repository() const;

	/// <summary>
	/// file repo tests
	/// </summary>
	void test_file_repository() const;

	/// <summary>
	/// service tests
	/// </summary>
	void test_service() const;

	/// <summary>
	/// tests file exportation
	/// </summary>
	void test_export_to_files() const;

	/// <summary>
	/// tests the undo functionality
	/// </summary>
	void test_undo() const;
};