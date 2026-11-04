// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29548592;
  double density_weight = 0.04230632;
  double prefix_weight = 0.36469551;
  double neighborhood_weight = 0.29650771;
  double late_weight = 0.06714428;
  double critical_weight = 0.08194455;
  unsigned budget = 33;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
