// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65532568;
  double density_weight = 0.18350672;
  double prefix_weight = 0.11409861;
  double neighborhood_weight = 0.34023140;
  double late_weight = 0.10816081;
  double critical_weight = 0.37503461;
  unsigned budget = 8;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
