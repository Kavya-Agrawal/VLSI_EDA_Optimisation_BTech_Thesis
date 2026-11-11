// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71184194;
  double density_weight = 0.32242598;
  double prefix_weight = 0.46129924;
  double neighborhood_weight = 0.12271447;
  double late_weight = 0.28941435;
  double critical_weight = 0.23435032;
  unsigned budget = 15;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
